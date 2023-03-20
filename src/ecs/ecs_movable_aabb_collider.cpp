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
    _velocityIndex = _parent.get().index<ECS_Velocity>();
    _physicsPositioned = _parent.get().index<ECS_PhysicsPositioned>();
}

void omniscia::core::ecs::ECS_MovableAABBCollider::collide(ECS_AABBCollider* another) {
    Vec2f selfScale = Vec2f{1.0, 1.0}; 
    Vec3f selfOldPosition = Vec3f{0.0, 0.0, 0.0}; 
    Vec3f selfNewPosition = Vec3f{0.0, 0.0, 0.0}; 
    Vec3f selfVelocity = Vec3f{0.0, 0.0, 0.0};

    if(_physicsPositioned.is_success()) {
        ECS_PhysicsPositioned &physicsPositionedComp = _parent.get().ref_unsafe(_physicsPositioned);
        selfOldPosition = physicsPositionedComp.get_old_position();
        selfNewPosition = physicsPositionedComp.get_new_position();
    } else if(posIndex.is_success()) {
        ECS_Positioned &positionComp = _parent.get().ref_unsafe(posIndex);
        selfOldPosition = positionComp.get_pos();
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

    Vec3f selfPosition = { selfNewPosition.x, selfOldPosition.y, selfOldPosition.z };

    {   //X axis collision
        if(_colliding == true) goto checkYCollision;

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
        f32 intersectionX1 = std::max(minX1, minX2);
        f32 intersectionX2 = std::min(maxX1, maxX2);
        f32 intersectionY1 = std::max(minY1, minY2);
        f32 intersectionY2 = std::min(maxY1, maxY2);
        f32 intersectionCenterX = (intersectionX1 + intersectionX2) / 2.0f;
        f32 intersectionCenterY = (intersectionY1 + intersectionY2) / 2.0f;

        /* Calculate collision side */
        CollisionSide tmpCollsionSide = NONE;
        f32 xOverlapDistLeft = maxX2 - minX1;
        f32 xOverlapDistRight = maxX1 - minX2;
        f32 yOverlapDistTop = maxY2 - minY1;
        f32 yOverlapDistBottom = maxY1 - minY2;
        f32 minOverlap = std::min({xOverlapDistLeft, xOverlapDistRight, yOverlapDistTop, yOverlapDistBottom});

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
    selfPosition = { selfOldPosition.x, selfNewPosition.y, selfOldPosition.z };
    {   //Y axis collision
        if(_collidingY == true) return;

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
        f32 intersectionX1 = std::max(minX1, minX2);
        f32 intersectionX2 = std::min(maxX1, maxX2);
        f32 intersectionY1 = std::max(minY1, minY2);
        f32 intersectionY2 = std::min(maxY1, maxY2);
        f32 intersectionCenterX = (intersectionX1 + intersectionX2) / 2.0f;
        f32 intersectionCenterY = (intersectionY1 + intersectionY2) / 2.0f;

        /* Calculate collision side */
        CollisionSide tmpCollsionSide = NONE;
        f32 xOverlapDistLeft = maxX2 - minX1;
        f32 xOverlapDistRight = maxX1 - minX2;
        f32 yOverlapDistTop = maxY2 - minY1;
        f32 yOverlapDistBottom = maxY1 - minY2;
        f32 minOverlap = std::min({xOverlapDistLeft, xOverlapDistRight, yOverlapDistTop, yOverlapDistBottom});

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

void omniscia::core::ecs::ECS_MovableAABBCollider::reset_collisions() {
    _colliding = false;
    _collidingY = false;
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
