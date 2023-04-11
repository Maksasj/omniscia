/**
 * @file 
 * ecs_aabb_collider.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _ECS_COMPONENT_AABB_COLLIDER_H_
#define _ECS_COMPONENT_AABB_COLLIDER_H_

#include <array>
#include <memory>
#include <iostream>
#include <algorithm>

#include "collision_side_type.h"
#include "ecs_box_collider_mesh.h"
#include "ecs_component.tpp"
#include "ecs_collision_mask.h"
#include "ecs_positioned.h"
#include "ecs_system.h"
#include "ecs_scaled.h"
#include "controls.h"
#include "entity.h"

namespace omniscia::core::ecs {
    using namespace omniscia::core;

    /**
     * @brief ECS_AABBCollider - component used for 
     * managing all simple aabb collider collision, 
     * also used by movable aabb collider 
    */
    class ECS_AABBCollider : public ECS_Component {
        protected:
            /**
             * @brief Pointer to the parent entity 
             * instance, used for reindexing and time sync 
            */
            Entity* _parent;

            /** @brief ECS_Index of the positioned component */
            ECS_Index<ECS_Positioned> posIndex;
            
            /** @brief ECS_Index of the scale component */
            ECS_Index<ECS_Scaled> scaleIndex;
            
            /** @brief ECS_Index of the box collider mesh component */
            ECS_Index<ECS_BoxColliderMesh> colliderMeshIndex;

            /** @brief Collision layer of the collider */
            u64 _collisionLayer;
            
            /** @brief Collision target layer of the collider */
            u64 _collisionLayerTarget;

            /* Collider variables */
            bool _colliding;
            ECS_AABBCollider* _collidedWith;
            Vec2f _collisionPoint;
            CollisionSide _collisionSide;

        public:
            friend class ECS_MovableAABBCollider;

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

            /* First argument is self collision layer, second argument is layers that can trigger collision for this component */
            ECS_AABBCollider(const u64& collisionLayer = CollisionMask_None, const u64& collisionLayerTarget = CollisionMask_None);
            
            /**
             * @brief Method used for checking if 
             * aabb collider is colliding
             * with another aabb collider
             * 
             * @param another pointer to the another aabb collider 
            */
            virtual void collide(ECS_AABBCollider* another);

            /**
             * @brief Resets all references to the
             * other aabb collider, if collision 
             * acquired last frame
            */
            virtual void reset_collisions();

            /**
             * @brief Getter that returns bolean is collider collides with another collider
             * 
             * @return true - collider is colliding
             * @return false - collider does not colliding
            */
            bool is_colliding() const;
            
            /**
             * @brief Getter used for getting collision layer of the collider
             * 
             * @return u64 collision layer of the aabb collider
            */
            u64 get_collision_layer() const;

            /**
             * @brief Returns pointer to the aabb 
             * collider, if collision acquired
             * 
             * @return ECS_AABBCollider* pointer to the the 
             * target aabb collider, that colliding with this collider
            */
            ECS_AABBCollider* get_colliding_with() const;

            /**
             * @brief Returns point of the collision
             * 
             * @return Vec2f point of the collision
            */
            Vec2f get_collision_point() const;
            
            /**
             * @brief Returns collision side, from which side collision acquired
             * 
             * @return collsion side from which side collision acquired
            */
            CollisionSide get_collision_side() const;

            /**
             * @brief Method used for clonning single 
             * component instance, allocates copy of
             * the current component and returns pointer to it
             * 
             * @return pointer to the new component instance
            */
            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_AABBCollider>(*this));
            }

            /**
             * @brief Virtual method used for 
             * calculating byte size of the component
             * 
             * @return byte size of the component
            */
            u64 byte_size() override {
                return sizeof(ECS_AABBCollider);
            }
    };

    class ECS_AABBColliderSystem : public ECS_System<ECS_AABBCollider> {
        private:
            ECS_AABBColliderSystem() {};
            ECS_AABBColliderSystem(ECS_AABBColliderSystem const&) {};
            void operator=(ECS_AABBColliderSystem const&) {};
        public:
            void update() {
                for(int i = 0; i < _components.size(); ++i) {
                    for(int j = 0; j < _components.size(); ++j) { 
                        if(i == j) continue;
    
                        _components[i]->collide(_components[j]);
                    }
                }
            }

            void reset() {
                for(int i = 0; i < _components.size(); ++i) {
                    _components[i]->reset_collisions();
                }  
            }

            static ECS_AABBColliderSystem& get_instance() {
                static ECS_AABBColliderSystem instance;
                return instance;
            }
    };
}

#endif
