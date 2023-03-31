#ifndef _ECS_COMPONENT_AABB_COLLIDER_H_
#define _ECS_COMPONENT_AABB_COLLIDER_H_

#include <array>
#include <memory>
#include <iostream>
#include <algorithm>

#include "collision_side_type.h"
#include "ecs_component.tpp"
#include "ecs_positioned.h"
#include "ecs_system.h"
#include "ecs_scaled.h"
#include "controls.h"
#include "entity.h"

namespace omniscia::core::ecs {
    using namespace omniscia::core;

    class ECS_AABBCollider : public ECS_Component {
        protected:
            Entity* _parent;

            ECS_Index<ECS_Positioned> posIndex;
            ECS_Index<ECS_Scaled> scaleIndex;

            /* Collider variables */
            bool _colliding;
            ECS_AABBCollider* _collidedWith;
            Vec2f _collisionPoint;
            CollisionSide _collisionSide;
        public:
            friend class ECS_MovableAABBCollider;

            void reindex(void* parent) override;
            void time_sync() override;

            ECS_AABBCollider();

            virtual void collide(ECS_AABBCollider* another);
            virtual void reset_collisions();

            bool is_colliding() const;
            ECS_AABBCollider* get_colliding_with() const;
            Vec2f get_collision_point() const;
            CollisionSide get_collision_side() const;

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_AABBCollider>(*this));
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
