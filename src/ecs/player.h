#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "entity.h"

#include "ecs_player_controller.h"
#include "ecs_sprite_renderer.h"
#include "ecs_sprite_animation.h"
#include "ecs_spritesheet_renderer.h"
#include "ecs_scaled.h"
#include "ecs_positioned.h"

namespace omniscia::core {
    class Player : public Entity {
        public:
            Player() {
                add(new ECS_Positioned());
                add(new ECS_Scaled({0.25, 0.25}));
                add(new ECS_SpriteAnimation({1.0, 1.0}, {0.2, 0.2}, {0.0, 0.6}, 5, true));
                add(new ECS_SpriteSheetRenderer("player-spritesheet", *this, 1));
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
