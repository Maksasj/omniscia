/**
 * @file 
 * ecs_movable_aabb_collider.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _ECS_COMPONENT_MOVABLE_AABB_COLLIDER_H_
#define _ECS_COMPONENT_MOVABLE_AABB_COLLIDER_H_

#include "ecs_physics_positioned.h"
#include "ecs_aabb_collider.h"
#include "ecs_velocity.h"

namespace omniscia::core::ecs {
    using namespace omni::types;
    using namespace omniscia::core;

    /**
     * @brief ECS_MovableAABBCollider - component that
     * used for collision detection between entities that
     * changes their position betweeen frames
    */
    class ECS_MovableAABBCollider : public ECS_AABBCollider {
        private:
            /** @brief ECS_Index of the velocity component */
            ECS_Index<ECS_Velocity> _velocityIndex;
            
            /** @brief ECS_Index of the physics positioned component */
            ECS_Index<ECS_PhysicsPositioned> _physicsPositioned;
        
            /* Collider variables */
            bool _collidingY;
            ECS_AABBCollider* _collidedWithY;
            Vec2f _collisionPointY;
            CollisionSide _collisionSideY;

        public:
            friend class omni::reflector::FieldFriendlyScope;
            friend class omni::reflector::Reflection<ECS_MovableAABBCollider>;

            /**
             * @brief Method used for time 
             * synchronization of the component
             * instance, binds component to the
             * system
            */
            void time_sync() override;

            /**
             * @brief Method that reindexes all indexes
             * that are required by this component,
             * also updates pointer to the parent entity index
             * 
             * @param parent - pointer to the parent 
             * entity instance
            */
            void reindex(void* parent) override;

            /**
             * @brief Default constructor of the ECS_MovableAABBCollider component
             * 
             * @param collisionLayer collision layer of the component
             * @param collisionLayerTarget target collision layer of the component
            */
            ECS_MovableAABBCollider(const u64& collisionLayer = CollisionMask_None, const u64& collisionLayerTarget = CollisionMask_None);

            /**
             * @brief Method used for checking if 
             * aabb collider is colliding
             * with another aabb collider
             * 
             * @param another pointer to the another aabb collider 
            */
            void collide(ECS_AABBCollider* another) override;
            
            /**
             * @brief Resets all references to the
             * other aabb collider, if collision 
             * acquired last frame
            */
            void reset_collisions() override;

            /**
             * @brief Getter that returns bolean is collider 
             * collides with another collider by x axis
             * 
             * @return true - collider is colliding
             * @return false - collider does not colliding
            */
            bool is_colliding_by_x() const;

            /**
             * @brief Returns pointer to the aabb 
             * collider, if collision acquired by x axis
             * 
             * @return ECS_AABBCollider* pointer to the the 
             * target aabb collider, that colliding with this collider
            */
            ECS_AABBCollider* get_colliding_with_by_x() const;
            
            /**
             * @brief Returns point of the collision on x axis
             * 
             * @return Vec2f point of the collision
            */
            Vec2f get_collision_point_by_x() const;

            /**
             * @brief Returns collision side, from which 
             * side collision acquired on x axis
             * 
             * @return collsion side from which side collision acquired
            */
            CollisionSide get_collision_side_by_x() const;
            
            /**
             * @brief Getter that returns bolean is collider 
             * collides with another collider by y axis
             * 
             * @return true - collider is colliding
             * @return false - collider does not colliding
            */
            bool is_colliding_by_y() const;
            
            /**
             * @brief Returns pointer to the aabb 
             * collider, if collision acquired by y axis
             * 
             * @return ECS_AABBCollider* pointer to the the 
             * target aabb collider, that colliding with this collider
            */
            ECS_AABBCollider* get_colliding_with_by_y() const;

            /**
             * @brief Returns point of the collision on y axis
             * 
             * @return Vec2f point of the collision
            */
            Vec2f get_collision_point_by_y() const;

            /**
             * @brief Returns collision side, from which 
             * side collision acquired on y axis
             * 
             * @return collsion side from which side collision acquired
            */
            CollisionSide get_collision_side_by_y() const;

            /**
             * @brief Method used for clonning single 
             * component instance, allocates copy of
             * the current component and returns pointer to it
             * 
             * @return pointer to the new component instance
            */
            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_MovableAABBCollider>(*this));
            }

            void _type_query(void* query) override {
                DebugFieldQuery::debug_component_edit_query<ECS_MovableAABBCollider>(*this);
            }
    };
}

OMNI_ADAPT_STRUCTURE_NAME(omniscia::core::ecs, ECS_MovableAABBCollider, _enabled, _collisionLayer, _collisionLayerTarget, _colliding, _collisionPoint, _collidingY, _collisionPointY);

#endif
