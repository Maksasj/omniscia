#include "ecs_player_controller.h"

omniscia::core::ecs::ECS_PlayerController::ECS_PlayerController(Entity& parent) : _parent(parent) {
    ECS_PlayerControllerSystem::get_instance().bind_component(this);
};

void omniscia::core::ecs::ECS_PlayerController::time_sync() {
    ECS_PlayerControllerSystem::get_instance().bind_component(this);
}

void  omniscia::core::ecs::ECS_PlayerController::reindex(void* parent) {
    _parent = *(Entity*)parent;

    velocityIndex = _parent.get().index<ECS_Velocity>();
    spriteFlipIndex = _parent.get().index<ECS_SpriteFlip>();
    spriteAnimationIndex = _parent.get().index<ECS_SpriteAnimation>();
    accelerationIndex = _parent.get().index<ECS_Acceleration>();
}

void  omniscia::core::ecs::ECS_PlayerController::control() {
    ECS_Velocity &velocityComp = _parent.get().ref_unsafe(velocityIndex);
    ECS_Acceleration &accelerationComp = _parent.get().ref_unsafe(accelerationIndex);
    accelerationComp.set_acceleration(Vec3f{0.0f, 0.0f, 0.0f});
        
    if(Controls::get(PlayerController::LEFT)) {
        accelerationComp.add_acceleration({-0.0001f, 0.0f, 0.0f});

        if(spriteFlipIndex.is_success()) {
            ECS_SpriteFlip& spriteFlip = _parent.get().ref_unsafe(spriteFlipIndex);
            spriteFlip.set_vertical_flip(true);
        }
    }
    
    if(Controls::get(PlayerController::RIGHT)) {
        accelerationComp.add_acceleration({0.0001f, 0.0f, 0.0f});

        if(spriteFlipIndex.is_success()) {
            ECS_SpriteFlip& spriteFlip = _parent.get().ref_unsafe(spriteFlipIndex);
            spriteFlip.set_vertical_flip(false);
        }
    }
}
