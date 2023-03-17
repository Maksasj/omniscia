#include "ecs_sprite_animation.h"

omniscia::core::ecs::ECS_SpriteAnimation::ECS_SpriteAnimation(const Vec2f& spriteUvSize,const Vec2f& spriteFrameSize, const Vec2f& startPossition, const u32& frameCount,const bool& direction) {
    _spriteUvSize = spriteUvSize;
    _spriteFrameSize = spriteFrameSize;
    _startPossition = startPossition;

    _frameCount = frameCount;
    _direction = direction;

    _currentFrame = 0;
    
    ECS_SpriteAnimationSystem::get_instance().bind_component(this);
};

void omniscia::core::ecs::ECS_SpriteAnimation::time_sync() {
    ECS_SpriteAnimationSystem::get_instance().bind_component(this);
}
