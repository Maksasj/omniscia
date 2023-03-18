#ifndef _ECS_COMPONENT_PLAYER_CONTOLLER_H_
#define _ECS_COMPONENT_PLAYER_CONTOLLER_H_

#include <array>
#include <memory>
#include <iostream>

#include "entity.h"

#include "ecs_system.h"
#include "ecs_velocity.h"
#include "ecs_component.tpp"
#include "controls.h"
#include "ecs_sprite_flip.h"

namespace omniscia::core::ecs {
    using namespace omniscia::core;

    class ECS_PlayerController : public ECS_Component {
        private:
            std::reference_wrapper<Entity> _parent;

            ECS_Index<ECS_Velocity> velocityIndex;
            ECS_Index<ECS_SpriteFlip> spriteFlipIndex;
        public:
            ECS_PlayerController(Entity& parent);

            void reindex(void* parent) override;
            void time_sync() override;

            void control();

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_PlayerController>(*this));
            }
    };

    class ECS_PlayerControllerSystem : public ECS_System<ECS_PlayerController> {
        private:
            ECS_PlayerControllerSystem() {};
            ECS_PlayerControllerSystem(ECS_PlayerControllerSystem const&) {};
            void operator=(ECS_PlayerControllerSystem const&) {};
        public:
            void update() {
                for(ECS_PlayerController* comp : _components) {
                    comp->control();
                }
            }

            static ECS_PlayerControllerSystem& get_instance() {
                static ECS_PlayerControllerSystem instance;
                return instance;
            }
    };
}

#endif
