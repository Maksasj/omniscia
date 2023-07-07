#include "ecs/gfx/ecs_sprite_animation.h"

omniscia::core::ecs::ECS_SpriteAnimation::ECS_SpriteAnimation(const std::string &animationId) {
    animation = AnimationManager::get_instance().get(animationId)->get_asset();
    _currentFrame = 0;
    _animationId = animationId;

    _tick = 0;

    ECS_SpriteAnimationSystem::get_instance().bind_component(this);
}

void omniscia::core::ecs::ECS_SpriteAnimation::time_sync() {
    ECS_SpriteAnimationSystem::get_instance().bind_component(this);
}

std::string omniscia::core::ecs::ECS_SpriteAnimation::get_animation() const {
    return _animationId;
}

omni::types::Vec2f omniscia::core::ecs::ECS_SpriteAnimation::get_frame_size() const {
    return animation->get_frame_size();
}

omni::types::Vec2f omniscia::core::ecs::ECS_SpriteAnimation::get_frame_offset() const {
    return animation->get_frame_offset(_currentFrame);
}

void omniscia::core::ecs::ECS_SpriteAnimation::set_animation(const std::string &animationId) {
    animation = AnimationManager::get_instance().get(animationId)->get_asset();
    _animationId = animationId;
}

void omniscia::core::ecs::ECS_SpriteAnimation::reset_animation() {
    _currentFrame = 0;
}

void omniscia::core::ecs::ECS_SpriteAnimation::update() {

};
