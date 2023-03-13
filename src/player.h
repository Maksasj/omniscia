#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "entity.h"

#include "ecs_player_controller.h"
#include "ecs_positioned.h"

namespace omniscia::core {
    class Player : public Entity {
        private:
            ECS_Index<ECS_PlayerController> pcIndex1;
            ECS_Index<ECS_PlayerController> pcIndex2;
        public:
            Player() {
                pcIndex1 = add_and_index(std::make_shared<ECS_PlayerController>());
                pcIndex2 = add_and_index(std::make_shared<ECS_PlayerController>());
            }

            void update() {
                std::shared_ptr<ECS_PlayerController> pc = try_index<ECS_PlayerController>(pcIndex1).value();
                
                ++pc.get()->pp;
            }

            int read() {
                std::shared_ptr<ECS_PlayerController> pc = try_index<ECS_PlayerController>(pcIndex1).value();

                return pc.get()->pp;
            }

            Player clone() {
                Player tmpPlayer = *this;
                clone_container_to(tmpPlayer);
                return tmpPlayer;
            }
    };
}

#endif
