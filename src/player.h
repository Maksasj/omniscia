#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "entity.h"

#include "ecs_player_controller.h"
#include "ecs_sprite_renderer.h"
#include "ecs_positioned.h"

namespace omniscia::core {
    class Player : public Entity {
        private:
            ECS_Index<ECS_PlayerController> _ECSPlayerController;
            ECS_Index<ECS_SpriteRenderer> _ECSSpriteRenderer;
            ECS_Index<ECS_Positioned> _ECSPositioned;
        public:
            Player() {
                _ECSPlayerController = add_and_index(ECS_PlayerController());
                _ECSSpriteRenderer = add_and_index(ECS_SpriteRenderer("jojo_texture"));
                _ECSPositioned = add_and_index(ECS_Positioned());
            }
 
            void render(Shader* shader) {
                auto& ecs_positioned_ref = try_ref<ECS_Positioned>(_ECSPositioned).value().get();
                auto& ecs_spriterenderer_ref = try_ref<ECS_SpriteRenderer>(_ECSSpriteRenderer).value().get();

                Vec3f pos = ecs_positioned_ref.get_pos();
                ecs_spriterenderer_ref.render(shader, Vec2f{pos.x, pos.y}, 0.0f, Vec2f{0.3f, 0.3f});
            }

            void update() {
                auto& ecs_positioned_ref = try_ref<ECS_Positioned>(_ECSPositioned).value().get();
                auto& ecs_playercontroller_ref = try_ref<ECS_PlayerController>(_ECSPlayerController).value().get();

                ecs_playercontroller_ref.lets_control(ecs_positioned_ref);
            }

            Player clone() {
                Player tmpPlayer = *this;
                clone_container_to(tmpPlayer);
                return tmpPlayer;
            }
    };
}

#endif
