#ifndef _ECS_COMPONENT_PLAYER_TIME_JUMP_CONTROLLER_H_
#define _ECS_COMPONENT_PLAYER_TIME_JUMP_CONTROLLER_H_

#include <array>
#include <memory>
#include <iostream>

#include "ecs_movable_aabb_collider.h"
#include "ecs_acceleration.h"
#include "ecs_component.tpp"
#include "ecs_velocity.h"
#include "ecs_system.h"
#include "timesystem.h"
#include "controls.h"
#include "entity.h"
#include "debug_ui.h"

namespace omniscia::core::ecs {
    using namespace omniscia::core;

    class ECS_PlayerTimeJumpController : public ECS_Component {
        private:
            Entity* _parent;
            
            ECS_Index<ECS_Velocity> velocityIndex;
            ECS_Index<ECS_MovableAABBCollider> movableAABBColliderIndex;
        public:
            ECS_PlayerTimeJumpController();

            void update();

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_PlayerTimeJumpController>(*this));
            }
    };

    class ECS_PlayerTimeJumpControllerSystem : public ECS_System<ECS_PlayerTimeJumpController> {
        private:
            ECS_PlayerTimeJumpControllerSystem() {};
            ECS_PlayerTimeJumpControllerSystem(ECS_PlayerTimeJumpControllerSystem const&) {};
            void operator=(ECS_PlayerTimeJumpControllerSystem const&) {};
        public:
            void update() {
                for(ECS_PlayerTimeJumpController* comp : _components) {
                    comp->update();
                }
            }

            static ECS_PlayerTimeJumpControllerSystem& get_instance() {
                static ECS_PlayerTimeJumpControllerSystem instance;
                return instance;
            }
    };
}

#endif
