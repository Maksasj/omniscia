#ifndef _ECS_2D_PHYSICS_RIGIDBODY_H_
#define _ECS_2D_PHYSICS_RIGIDBODY_H_

#include <array>
#include <memory>
#include <iostream>

#include "entity.h"
#include "ecs_system.h" 

#include "ecs_component.tpp"
//#include "controls.h"

#include "ecs_movable_aabb_collider.h"
#include "ecs_positioned.h"
#include "ecs_velocity.h"
#include "ecs_friction.h"
#include "ecs_acceleration.h"

#include "timesystem.h"

namespace omniscia::core::ecs {
    class ECS_2DPhysicsRigidbody : public ECS_Component {
        private:
            std::reference_wrapper<Entity> _parent;

            ECS_Index<ECS_Positioned> _posIndex;
            ECS_Index<ECS_MovableAABBCollider> _colliderIndex;

            ECS_Index<ECS_Velocity> _velocityIndex;
            ECS_Index<ECS_Acceleration> _accelerationIndex;
            ECS_Index<ECS_Friction> _frictionIndex;
        public:
            void time_sync() override;
            void reindex(void* parent) override;

            ECS_2DPhysicsRigidbody(Entity& parent);

            void update();

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_2DPhysicsRigidbody>(*this));
            }
    };

    class ECS_2DPhysicsRigidbodySystem : public ECS_System<ECS_2DPhysicsRigidbody> {
        private:
            ECS_2DPhysicsRigidbodySystem() {};
            ECS_2DPhysicsRigidbodySystem(ECS_2DPhysicsRigidbodySystem const&) {};
            void operator=(ECS_2DPhysicsRigidbodySystem const&) {};
        public:
            void update() {
                for(ECS_2DPhysicsRigidbody* comp : _components) {
                    comp->update();
                }
            }

            static ECS_2DPhysicsRigidbodySystem& get_instance() {
                static ECS_2DPhysicsRigidbodySystem instance;
                return instance;
            }
    };
}

#endif