#include "ecs_sprite_animation.h"

omniscia::core::ecs::ECS_SpriteAnimation::ECS_SpriteAnimation(const std::string &animationId) {
    animation = AnimationManager::get_instance().get(animationId)->get_asset();
    _currentFrame = 0;

    ECS_SpriteAnimationSystem::get_instance().bind_component(this);
}

void omniscia::core::ecs::ECS_SpriteAnimation::time_sync() {
    ECS_SpriteAnimationSystem::get_instance().bind_component(this);
}

omniscia::core::Vec2f omniscia::core::ecs::ECS_SpriteAnimation::get_frame_size() const {
    return animation->get_frame_size();
}

omniscia::core::Vec2f omniscia::core::ecs::ECS_SpriteAnimation::get_frame_offset() const {
    return animation->get_frame_offset(_currentFrame);
}

void omniscia::core::ecs::ECS_SpriteAnimation::set_animation(const std::string &animationId) {
    animation = AnimationManager::get_instance().get(animationId)->get_asset();
}

void omniscia::core::ecs::ECS_SpriteAnimation::update() {
    static u64 tick = 0;
    ++tick;

    if(tick % 120 == 0) {
        ++_currentFrame;

        if(_currentFrame >= animation->get_frame_count()) {
            _currentFrame = 0;
        }
    }
};
