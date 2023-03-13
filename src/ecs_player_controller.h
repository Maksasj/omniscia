#ifndef _ECS_COMPONENT_PLAYER_CONTOLLER_H_
#define _ECS_COMPONENT_PLAYER_CONTOLLER_H_

#include <array>
#include <memory>
#include <iostream>

#include "ecs_component.tpp"
#include "controls.h"

namespace omniscia::core::ecs {
    using namespace omniscia::core;

    class ECS_PlayerController : public ECS_Component {
        private:

        public:
            int pp;
            ECS_PlayerController() : pp(0) {}

            void lets_control() {
                if(Controls::get(PlayerController::JUMP))
                    std::cout << "Jumping \n";

                if(Controls::get(PlayerController::LEFT))
                    std::cout << "Left \n";

                if(Controls::get(PlayerController::RIGHT))
                    std::cout << "Right \n";
            }

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_PlayerController>(*this));
            }
    };
}

#endif