#include "ecs_movable_aabb_collider.h"

omniscia::core::ecs::ECS_MovableAABBCollider::ECS_MovableAABBCollider(Entity& parent) : ECS_AABBCollider(parent) {
    _colliding = false;
    _collidedWith = nullptr;
    _collisionPoint = Vec2f{0.0, 0.0};
    _collisionSide = CollisionSide::NONE;
    
    _collidingY = false;
    _collidedWithY = nullptr;
    _collisionPointY = Vec2f{0.0, 0.0};
    _collisionSideY = CollisionSide::NONE;

    ECS_AABBColliderSystem::get_instance().bind_component(this);
};

void omniscia::core::ecs::ECS_MovableAABBCollider::time_sync() {
    ECS_AABBColliderSystem::get_instance().bind_component(this);
}

void omniscia::core::ecs::ECS_MovableAABBCollider::reindex(void* parent) {
    _parent = *(Entity*)parent;

    posIndex = _parent.get().index<ECS_Positioned>();
    scaleIndex = _parent.get().index<ECS_Scaled>();
    velocityIndex = _parent.get().index<ECS_Velocity>();
}

void omniscia::core::ecs::ECS_MovableAABBCollider::collide(ECS_AABBCollider* another) {
    Vec2f selfScale = Vec2f{1.0, 1.0}; 
    Vec3f selfOldPosition = Vec3f{0.0, 0.0, 0.0}; 
    Vec3f selfVelocity = Vec3f{0.0, 0.0, 0.0};

    if(posIndex.is_success()) {
        ECS_Positioned &positionComp = _parent.get().ref_unsafe(posIndex);
        selfOldPosition = positionComp.get_pos();
    }

    if(scaleIndex.is_success()) {
        ECS_Scaled &scaleComp = _parent.get().ref_unsafe(scaleIndex);
        selfScale = scaleComp.get_scale();
    }

    if(velocityIndex.is_success()) {
        ECS_Velocity &velocityComp = _parent.get().ref_unsafe(velocityIndex);
        selfVelocity = velocityComp.get_velocity();
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

    Vec3f selfPosition = { selfOldPosition.x + selfVelocity.x, selfOldPosition.y, selfOldPosition.z };

    {   //X axis collision
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
            goto checkYCollision;
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

    checkYCollision:
    selfPosition = { selfOldPosition.x, selfOldPosition.y + selfVelocity.y, selfOldPosition.z };
    {   //Y axis collision
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
            _collidingY = false;
            _collidedWithY = nullptr;
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

        _collidingY = true;
        _collidedWithY = another;
        _collisionPointY = { intersectionCenterX, intersectionCenterY };
        _collisionSideY = tmpCollsionSide;
    }
}

bool omniscia::core::ecs::ECS_MovableAABBCollider::is_colliding_by_x() const {
    return _colliding;
}

omniscia::core::ecs::ECS_AABBCollider* omniscia::core::ecs::ECS_MovableAABBCollider::get_colliding_with_by_x() const {
    return _collidedWith;
}

omniscia::core::Vec2f omniscia::core::ecs::ECS_MovableAABBCollider::get_collision_point_by_x() const {
    return _collisionPoint;
}

omniscia::core::ecs::CollisionSide omniscia::core::ecs::ECS_MovableAABBCollider::get_collision_side_by_x() const {
    return _collisionSide;
}

bool omniscia::core::ecs::ECS_MovableAABBCollider::is_colliding_by_y() const {
    return _collidingY;
}

omniscia::core::ecs::ECS_AABBCollider* omniscia::core::ecs::ECS_MovableAABBCollider::get_colliding_with_by_y() const {
    return _collidedWithY;
}

omniscia::core::Vec2f omniscia::core::ecs::ECS_MovableAABBCollider::get_collision_point_by_y() const {
    return _collisionPointY;
}

omniscia::core::ecs::CollisionSide omniscia::core::ecs::ECS_MovableAABBCollider::get_collision_side_by_y() const {
    return _collisionSideY;
}
