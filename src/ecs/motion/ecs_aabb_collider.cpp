#include "ecs_aabb_collider.h"

omniscia::core::ecs::ECS_AABBCollider::ECS_AABBCollider(const u64& collisionLayer, const u64& collisionLayerTarget) {
    _colliding = false;
    _collidedWith = nullptr;
    _collisionPoint = Vec2f{0.0, 0.0};
    _collisionSide = CollisionSide::NONE;

    _collisionLayer = collisionLayer;
    _collisionLayerTarget = collisionLayerTarget;
    
    ECS_AABBColliderSystem::get_instance().bind_component(this);
};

void omniscia::core::ecs::ECS_AABBCollider::time_sync() {
    ECS_AABBColliderSystem::get_instance().bind_component(this);
}

void omniscia::core::ecs::ECS_AABBCollider::reindex(void* parent) {
    _parent = (Entity*)parent;

    posIndex = _parent->index<ECS_Positioned>();
    scaleIndex = _parent->index<ECS_Scaled>();
    colliderMeshIndex = _parent->index<ECS_BoxColliderMesh>();
}

void omniscia::core::ecs::ECS_AABBCollider::collide(ECS_AABBCollider* another) {
    if(!(_collisionLayerTarget & another->_collisionLayer)) 
        return;
    
    if(_parent == another->_parent)
        return;

    Vec2f selfScale = Vec2f{1.0f, 1.0f}; 
    Vec3f selfPosition = Vec3f{0.0f, 0.0f, 0.0f};
    Vec2f selfCollisionXRanges = Vec2f{1.0f, 1.0f};
    Vec2f selfCollisionYRanges = Vec2f{1.0f, 1.0f};
    
    if(posIndex.is_success()) {
        ECS_Positioned &positionComp = _parent->ref_unsafe(posIndex);
        selfPosition = positionComp.get_pos();
    }

    if(scaleIndex.is_success()) {
        ECS_Scaled &scaleComp = _parent->ref_unsafe(scaleIndex);
        selfScale = scaleComp.get_scale();
    }

    if(colliderMeshIndex.is_success()) {
        ECS_BoxColliderMesh &boxColliderMeshComp = _parent->ref_unsafe(colliderMeshIndex);
        selfCollisionXRanges = boxColliderMeshComp.get_x_collision_ranges();
        selfCollisionYRanges = boxColliderMeshComp.get_y_collision_ranges();
    }

    Vec2f anotherScale = Vec2f{1.0, 1.0}; 
    Vec3f anotherPosition = Vec3f{0.0, 0.0, 0.0}; 
    Vec2f anotherCollisionXRanges = Vec2f{1.0f, 1.0f};
    Vec2f anotherCollisionYRanges = Vec2f{1.0f, 1.0f};

    if(another->posIndex.is_success()) {
        ECS_Positioned &positionComp = another->_parent->ref_unsafe(another->posIndex);
        anotherPosition = positionComp.get_pos();
    }

    if(another->scaleIndex.is_success()) {
        ECS_Scaled &scaleComp = another->_parent->ref_unsafe(another->scaleIndex);
        anotherScale = scaleComp.get_scale();
    }

    if(another->colliderMeshIndex.is_success()) {
        ECS_BoxColliderMesh &boxColliderMeshComp = another->_parent->ref_unsafe(another->colliderMeshIndex);
        anotherCollisionXRanges = boxColliderMeshComp.get_x_collision_ranges();
        anotherCollisionYRanges = boxColliderMeshComp.get_y_collision_ranges();
    }

    f32 minX1 = selfPosition.x - selfScale.x * selfCollisionXRanges.x;
    f32 maxX1 = selfPosition.x + selfScale.x * selfCollisionXRanges.y;
    f32 minY1 = selfPosition.y - selfScale.y * selfCollisionYRanges.x;
    f32 maxY1 = selfPosition.y + selfScale.y * selfCollisionYRanges.y;

    f32 minX2 = anotherPosition.x - anotherScale.x * anotherCollisionXRanges.x;
    f32 maxX2 = anotherPosition.x + anotherScale.x * anotherCollisionXRanges.y;
    f32 minY2 = anotherPosition.y - anotherScale.y * anotherCollisionYRanges.x;
    f32 maxY2 = anotherPosition.y + anotherScale.y * anotherCollisionYRanges.y;

    u8 xOverlap = (minX1 <= maxX2) && (maxX1 >= minX2);
    u8 yOverlap = (minY1 <= maxY2) && (maxY1 >= minY2);

    if(!(xOverlap && yOverlap) && _colliding != true) {
        _colliding = false;
        _collidedWith = nullptr;
        return;
    }

    /* Calculate collision point */
    float intersectionX1 = std::max(minX1, minX2);
    float intersectionX2 = std::min(maxX1, maxX2);
    float intersectionY1 = std::max(minY1, minY2);
    float intersectionY2 = std::min(maxY1, maxY2);
    float intersectionCenterX = (intersectionX1 + intersectionX2) / 2.0f;
    float intersectionCenterY = (intersectionY1 + intersectionY2) / 2.0f;

    /* Calculate collision side */
    CollisionSide tmpCollsionSide = NONE;
    float xOverlapDistLeft = maxX2 - minX1;
    float xOverlapDistRight = maxX1 - minX2;
    float yOverlapDistTop = maxY2 - minY1;
    float yOverlapDistBottom = maxY1 - minY2;
    float minOverlap = std::min({xOverlapDistLeft, xOverlapDistRight, yOverlapDistTop, yOverlapDistBottom});

    if (minOverlap == xOverlapDistLeft) {
        tmpCollsionSide = CollisionSide::LEFT;
    } else if (minOverlap == xOverlapDistRight) {
        tmpCollsionSide = CollisionSide::RIGHT;
    } else if (minOverlap == yOverlapDistTop) {
        tmpCollsionSide = CollisionSide::TOP;
    } else if (minOverlap == yOverlapDistBottom) {
        tmpCollsionSide = CollisionSide::BOTTOM;
    }

    _colliding = true;
    _collidedWith = another;
    _collisionPoint = { intersectionCenterX, intersectionCenterY };
    _collisionSide = tmpCollsionSide;
}

void omniscia::core::ecs::ECS_AABBCollider::reset_collisions() {
    _colliding = false;
}

bool omniscia::core::ecs::ECS_AABBCollider::is_colliding() const {
    return _colliding;
}

u64 omniscia::core::ecs::ECS_AABBCollider::get_collision_layer() const {
    return _collisionLayer;
}

omniscia::core::ecs::ECS_AABBCollider* omniscia::core::ecs::ECS_AABBCollider::get_colliding_with() const {
    return _collidedWith;
}

omniscia::core::Vec2f omniscia::core::ecs::ECS_AABBCollider::get_collision_point() const {
    return _collisionPoint;
}

omniscia::core::ecs::CollisionSide omniscia::core::ecs::ECS_AABBCollider::get_collision_side() const {
    return _collisionSide;
}
