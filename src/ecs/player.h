#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "entity.h"

#include "ecs_player_controller.h"
#include "ecs_sprite_renderer.h"
#include "ecs_positioned.h"

namespace omniscia::core {
    class Player : public Entity {
        public:
            Player() {
                add(new ECS_Positioned(*this));
                add(new ECS_SpriteRenderer("player", *this, 1));
                add(new ECS_PlayerController(*this));
            }

            Player clone() {
                Player tmpPlayer = *this;
                clone_container_to(tmpPlayer);
                return tmpPlayer;
            }
    };
}

#endif
