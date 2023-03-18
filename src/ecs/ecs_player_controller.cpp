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
}

void  omniscia::core::ecs::ECS_PlayerController::control() {
    ECS_Velocity &velocityComp = _parent.get().ref_unsafe(velocityIndex);
    Vec3f velocity = velocityComp.get_velocity();

    if(Controls::get(PlayerController::JUMP)) {
        //if(velocity.y == 0) {
            velocityComp.add_velocity(Vec3f{0.0f, 0.00005f, 0.0f});
        //}
    }

    if(Controls::get(PlayerController::DOWN)) {
        //if(velocity.y == 0) {
            velocityComp.add_velocity(Vec3f{0.0f, -0.00005f, 0.0f});
        //}
    }
        
    if(Controls::get(PlayerController::LEFT)) {
        velocityComp.add_velocity(Vec3f{-0.00005f, 0.0f, 0.0f});

        if(spriteFlipIndex.is_success()) {
            ECS_SpriteFlip& spriteFlip = _parent.get().ref_unsafe(spriteFlipIndex);
            spriteFlip.set_vertical_flip(true);
        }
    }
    
    if(Controls::get(PlayerController::RIGHT)) {
        velocityComp.add_velocity(Vec3f{0.00005f, 0.0f, 0.0f});

        if(spriteFlipIndex.is_success()) {
            ECS_SpriteFlip& spriteFlip = _parent.get().ref_unsafe(spriteFlipIndex);
            spriteFlip.set_vertical_flip(false);
        }
    }

    velocityComp.clamp_velocity();
}
