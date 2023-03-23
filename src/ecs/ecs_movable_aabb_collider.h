#ifndef _ECS_COMPONENT_MOVABLE_AABB_COLLIDER_H_
#define _ECS_COMPONENT_MOVABLE_AABB_COLLIDER_H_

#include "ecs_physics_positioned.h"
#include "ecs_aabb_collider.h"
#include "ecs_velocity.h"

namespace omniscia::core::ecs {
    using namespace omniscia::core;

    class ECS_MovableAABBCollider : public ECS_AABBCollider {
        private:
            ECS_Index<ECS_Velocity> _velocityIndex;
            ECS_Index<ECS_PhysicsPositioned> _physicsPositioned;
        
            /* Collider variables */
            bool _collidingY;
            ECS_AABBCollider* _collidedWithY;
            Vec2f _collisionPointY;
            CollisionSide _collisionSideY;
        public:
            ECS_MovableAABBCollider(Entity& parent);

            void reindex(void* parent) override;
            void time_sync() override;

            void collide(ECS_AABBCollider* another) override;
            void reset_collisions() override;

            bool is_colliding_by_x() const;
            ECS_AABBCollider* get_colliding_with_by_x() const;
            Vec2f get_collision_point_by_x() const;
            CollisionSide get_collision_side_by_x() const;
            
            bool is_colliding_by_y() const;
            ECS_AABBCollider* get_colliding_with_by_y() const;
            Vec2f get_collision_point_by_y() const;
            CollisionSide get_collision_side_by_y() const;

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_MovableAABBCollider>(*this));
            }
    };
}

#endif
