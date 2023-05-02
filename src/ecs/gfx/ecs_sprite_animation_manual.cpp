#include "ecs_sprite_animation_manual.h"

omniscia::core::ecs::ECS_SpriteAnimationManual::ECS_SpriteAnimationManual(const std::string &animationId) : ECS_SpriteAnimation(animationId) {

}

void omniscia::core::ecs::ECS_SpriteAnimationManual::set_frame(const u64& frame) {
    _currentFrame = frame % animation->get_frame_count();
}

void omniscia::core::ecs::ECS_SpriteAnimationManual::update() {

};
