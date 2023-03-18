#include "ecs_aabb_collider.h"

omniscia::core::ecs::ECS_AABBCollider::ECS_AABBCollider(Entity& parent) : _parent(parent) {
    _colliding = false;
    _collidedWith = nullptr;
    _collisionPoint = Vec2f{0.0, 0.0};
    _collisionSide = CollisionSide::NONE;
    
    ECS_AABBColliderSystem::get_instance().bind_component(this);
};

void omniscia::core::ecs::ECS_AABBCollider::time_sync() {
    ECS_AABBColliderSystem::get_instance().bind_component(this);
}

void omniscia::core::ecs::ECS_AABBCollider::reindex(void* parent) {
    _parent = *(Entity*)parent;

    posIndex = _parent.get().index<ECS_Positioned>();
    scaleIndex = _parent.get().index<ECS_Scaled>();
}

void omniscia::core::ecs::ECS_AABBCollider::collide(ECS_AABBCollider* another) {
    Vec2f selfScale = Vec2f{1.0, 1.0}; 
    Vec3f selfPosition = Vec3f{0.0, 0.0, 0.0}; 
    
    if(posIndex.is_success()) {
        ECS_Positioned &positionComp = _parent.get().ref_unsafe(posIndex);
        selfPosition = positionComp.get_pos();
    }

    if(scaleIndex.is_success()) {
        ECS_Scaled &scaleComp = _parent.get().ref_unsafe(scaleIndex);
        selfScale = scaleComp.get_scale();
    }

    Vec2f anotherScale = Vec2f{1.0, 1.0}; 
    Vec3f anotherPosition = Vec3f{0.0, 0.0, 0.0}; 

    if(another->posIndex.is_success()) {
        ECS_Positioned &positionComp = another->_parent.get().ref_unsafe(another->posIndex);
        anotherPosition = positionComp.get_pos();
    }

    if(another->scaleIndex.is_success()) {
        ECS_Scaled &scaleComp = another->_parent.get().ref_unsafe(another->scaleIndex);
        anotherScale = scaleComp.get_scale();
    }

    f32 minX1 = selfPosition.x - selfScale.x;
    f32 maxX1 = selfPosition.x + selfScale.x;
    f32 minY1 = selfPosition.y - selfScale.y;
    f32 maxY1 = selfPosition.y + selfScale.y;

    f32 minX2 = anotherPosition.x - anotherScale.x;
    f32 maxX2 = anotherPosition.x + anotherScale.x;
    f32 minY2 = anotherPosition.y - anotherScale.y;
    f32 maxY2 = anotherPosition.y + anotherScale.y;

    u8 xOverlap = (minX1 <= maxX2) && (maxX1 >= minX2);
    u8 yOverlap = (minY1 <= maxY2) && (maxY1 >= minY2);

    if(!(xOverlap && yOverlap)) {
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

bool omniscia::core::ecs::ECS_AABBCollider::is_colliding() const {
    return _colliding;
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
