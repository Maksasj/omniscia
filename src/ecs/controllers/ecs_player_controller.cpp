#include "ecs_player_controller.h"

omniscia::core::ecs::ECS_PlayerController::ECS_PlayerController() {
    ECS_PlayerControllerSystem::get_instance().bind_component(this);
};

void omniscia::core::ecs::ECS_PlayerController::time_sync() {
    ECS_PlayerControllerSystem::get_instance().bind_component(this);
}

void  omniscia::core::ecs::ECS_PlayerController::reindex(void* parent) {
    _parent = (Entity*)parent;

    velocityIndex = _parent->index<ECS_Velocity>();
    spriteFlipIndex = _parent->index<ECS_SpriteFlip>();
    spriteAnimationIndex = _parent->index<ECS_SpriteAnimation>();
    accelerationIndex = _parent->index<ECS_Acceleration>();
}

void  omniscia::core::ecs::ECS_PlayerController::control() {
    ECS_Velocity &velocityComp = _parent->ref_unsafe(velocityIndex);
    ECS_Acceleration &accelerationComp = _parent->ref_unsafe(accelerationIndex);
    Vec3f& acceleration = accelerationComp.ref_acceleration();
    Vec3f& velocity = velocityComp.ref_velocity();

    bool isMoving = false;

    if(Controls::get_instance().get(PlayerController::LEFT)) {
        acceleration.x -= 0.0001f;

        if(spriteFlipIndex.is_success()) {
            ECS_SpriteFlip& spriteFlip = _parent->ref_unsafe(spriteFlipIndex);
            spriteFlip.set_vertical_flip(true);
        }

        isMoving = true;
    }
    
    if(Controls::get_instance().get(PlayerController::RIGHT)) {
        acceleration.x += 0.0001f;

        if(spriteFlipIndex.is_success()) {
            ECS_SpriteFlip& spriteFlip = _parent->ref_unsafe(spriteFlipIndex);
            spriteFlip.set_vertical_flip(false);
        }

        isMoving = true;
    }
    
    if(!spriteAnimationIndex.is_success()) return;
    ECS_SpriteAnimation& spriteAnimationComp = _parent->ref_unsafe(spriteAnimationIndex);
    std::string currentAnimation = spriteAnimationComp.get_animation();

    if(isMoving && currentAnimation == "player-idle-animation") {
        spriteAnimationComp.set_animation("player-run-animation");
        spriteAnimationComp.reset_animation();
        return;
    }

    if(!isMoving && currentAnimation != "player-idle-animation") {
        spriteAnimationComp.set_animation("player-idle-animation");
        spriteAnimationComp.reset_animation();
    }
}
