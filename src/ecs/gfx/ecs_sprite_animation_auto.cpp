#include "ecs_sprite_animation_auto.h"

omniscia::core::ecs::ECS_SpriteAnimationAuto::ECS_SpriteAnimationAuto(const std::string &animationId) : ECS_SpriteAnimation(animationId) {

}

void omniscia::core::ecs::ECS_SpriteAnimationAuto::update() {
    if(animation == nullptr)
        return;

    ++_tick;

    if(_tick % animation->_animationSpeed == 0) {
        ++_currentFrame;

        if(_currentFrame >= animation->get_frame_count()) {
            _currentFrame = 0;
        }
    }
};
