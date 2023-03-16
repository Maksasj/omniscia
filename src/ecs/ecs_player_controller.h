#ifndef _ECS_COMPONENT_PLAYER_CONTOLLER_H_
#define _ECS_COMPONENT_PLAYER_CONTOLLER_H_

#include <array>
#include <memory>
#include <iostream>

#include "entity.h"

#include "ecs_system.h"
#include "ecs_positioned.h"
#include "ecs_component.tpp"
#include "controls.h"

namespace omniscia::core::ecs {
    using namespace omniscia::core;

    class ECS_PlayerController : public ECS_Component {
        private:
            std::reference_wrapper<Entity> _parent;

            ECS_Index<ECS_Positioned> posIndex;
        public:
            ECS_PlayerController(Entity& parent);

            void reindex(void* parent) override {
                _parent = *(Entity*)parent;

                posIndex = _parent.get().index<ECS_Positioned>();
            }

            void time_sync() override;

            void control() {
                ECS_Positioned &position = _parent.get().ref_unsafe(posIndex);

                if(Controls::get(PlayerController::JUMP))
                    position.move_pos(Vec3f{0.0f, 0.001f, 0.0f});
                
                if(Controls::get(PlayerController::DOWN))
                    position.move_pos(Vec3f{0.0f, -0.001f, 0.0f});
                    
                if(Controls::get(PlayerController::LEFT))
                    position.move_pos(Vec3f{-0.001f, 0.0f, 0.0f});
                
                if(Controls::get(PlayerController::RIGHT))
                    position.move_pos(Vec3f{0.001f, 0.0f, 0.0f});
                
            }

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
