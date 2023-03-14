#ifndef _ECS_COMPONENT_PLAYER_CONTOLLER_H_
#define _ECS_COMPONENT_PLAYER_CONTOLLER_H_

#include <array>
#include <memory>
#include <iostream>

#include "ecs_positioned.h"
#include "ecs_component.tpp"
#include "controls.h"

namespace omniscia::core::ecs {
    using namespace omniscia::core;

    class ECS_PlayerController : public ECS_Component {
        private:

        public:
            ECS_PlayerController() {}

            void lets_control(ECS_Positioned &position) {
                if(Controls::get(PlayerController::JUMP)) {
                    position.move_pos(Vec3f{0.0f, 0.3f, 0.0f});
                }

                if(Controls::get(PlayerController::LEFT)) {
                    position.move_pos(Vec3f{-0.001f, 0.0f, 0.0f});
                }

                if(Controls::get(PlayerController::RIGHT)) {
                    position.move_pos(Vec3f{0.001f, 0.0f, 0.0f});
                }
            }

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_PlayerController>(*this));
            }
    };
}

#endif
