#ifndef _ECS_COMPONENT_PLAYER_JUMP_H_
#define _ECS_COMPONENT_PLAYER_JUMP_H_

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

namespace omniscia::core::ecs {
    using namespace omniscia::core;

    class ECS_PlayerJump : public ECS_Component {
        private:
            Entity* _parent;
            
            ECS_Index<ECS_Velocity> velocityIndex;
            ECS_Index<ECS_MovableAABBCollider> movableAABBColliderIndex;
        public:
            void reindex(void* parent) override;
            void time_sync() override;

            ECS_PlayerJump();

            void update();

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_PlayerJump>(*this));
            }
    };

    class ECS_PlayerJumpSystem : public ECS_System<ECS_PlayerJump> {
        private:
            ECS_PlayerJumpSystem() {};
            ECS_PlayerJumpSystem(ECS_PlayerJumpSystem const&) {};
            void operator=(ECS_PlayerJumpSystem const&) {};
        public:
            void update() {
                for(ECS_PlayerJump* comp : _components) {
                    comp->update();
                }
            }

            static ECS_PlayerJumpSystem& get_instance() {
                static ECS_PlayerJumpSystem instance;
                return instance;
            }
    };
}

#endif
