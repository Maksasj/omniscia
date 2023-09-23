#include "ecs/controllers/ecs_crab_controller.h"

omniscia::core::ecs::ECS_CrabController::ECS_CrabController() : ECS_StateMachineBase() {
    ECS_StateMachineBaseSystem::get_instance().bind_component(this);
    switch_state<ECS_CrabController>(&ECS_CrabController::crab_idle_state);
};

void omniscia::core::ecs::ECS_CrabController::time_sync() {
    ECS_StateMachineBaseSystem::get_instance().bind_component(this);
}

void omniscia::core::ecs::ECS_CrabController::reindex(void* parent) {
    _parent = (Entity*) parent;

    _accelerationIndex = _parent->index<ECS_Acceleration>();
    _spriteFlipIndex = _parent->index<ECS_SpriteFlip>();
    _spriteAnimationIndex = _parent->index<ECS_SpriteAnimation>();
    _colliderIndex = _parent->index<ECS_MovableAABBCollider>();
    _velocityIndex = _parent->index<ECS_Velocity>();
    _soundEmitterIndex = _parent->index<ECS_SoundEmitter>();
}

void omniscia::core::ecs::ECS_CrabController::crab_run_right_state() {
    if(!_accelerationIndex.is_success()) return;
    if(!_spriteFlipIndex.is_success()) return;
    if(!_spriteAnimationIndex.is_success()) return;
    if(!_colliderIndex.is_success()) return;
    if(!_velocityIndex.is_success()) return;
    if(!_soundEmitterIndex.is_success()) return;

    ECS_SoundEmitter& soundEmitterComp = _parent->ref_unsafe(_soundEmitterIndex);
    ECS_MovableAABBCollider& colliderComp = _parent->ref_unsafe(_colliderIndex);
    ECS_Acceleration &accelerationComp = _parent->ref_unsafe(_accelerationIndex);
    ECS_SpriteFlip& spriteFlipComp = _parent->ref_unsafe(_spriteFlipIndex);
    ECS_SpriteAnimation& spriteAnimationComp = _parent->ref_unsafe(_spriteAnimationIndex);

    Vec3f& acceleration = accelerationComp.ref_acceleration();

    if(colliderComp.is_colliding_by_x()) {
        spriteFlipComp.set_vertical_flip(false);
        switch_state<ECS_CrabController>(&ECS_CrabController::crab_run_left_state);
    } else {
        acceleration.x = 0.000002f;
    }

    const u64 random = rand();

    /*
    switch (random % 100) {
        case 0:
            soundEmitterComp.play("walk_1");
            break;
        case 1:
            soundEmitterComp.play("walk_2");
            break;
        case 2:
            soundEmitterComp.play("walk_3");
            break;
        case 3:
            soundEmitterComp.play("walk_4");
            break;
        default:
            break;
    }
    */

    if(random % 7000 != 0) return;

    spriteAnimationComp.set_animation("crab-idle-animation");
    switch_state<ECS_CrabController>(&ECS_CrabController::crab_idle_state);
}

void omniscia::core::ecs::ECS_CrabController::crab_run_left_state() {
    if(!_accelerationIndex.is_success()) return;
    if(!_spriteFlipIndex.is_success()) return;
    if(!_spriteAnimationIndex.is_success()) return;
    if(!_colliderIndex.is_success()) return;
    if(!_velocityIndex.is_success()) return;
    if(!_soundEmitterIndex.is_success()) return;

    ECS_SoundEmitter& soundEmitterComp = _parent->ref_unsafe(_soundEmitterIndex);
    ECS_MovableAABBCollider& colliderComp = _parent->ref_unsafe(_colliderIndex);
    ECS_Acceleration &accelerationComp = _parent->ref_unsafe(_accelerationIndex);
    ECS_SpriteFlip& spriteFlipComp = _parent->ref_unsafe(_spriteFlipIndex);
    ECS_SpriteAnimation& spriteAnimationComp = _parent->ref_unsafe(_spriteAnimationIndex);
    
    Vec3f& acceleration = accelerationComp.ref_acceleration();

    if(colliderComp.is_colliding_by_x()) {
        spriteFlipComp.set_vertical_flip(true);
        switch_state<ECS_CrabController>(&ECS_CrabController::crab_run_right_state);
    } else {
        acceleration.x = -0.000002f;
    }

    const u64 random = rand();

    /*
    switch (random % 100) {
        case 0:
            soundEmitterComp.play("walk_1");
            break;
        case 1:
            soundEmitterComp.play("walk_2");
            break;
        case 2:
            soundEmitterComp.play("walk_3");
            break;
        case 3:
            soundEmitterComp.play("walk_4");
            break;
        default:
            break;
    }
    */

    if(random % 7000 != 0) return;

    spriteAnimationComp.set_animation("crab-idle-animation");
    switch_state<ECS_CrabController>(&ECS_CrabController::crab_idle_state);
}

void omniscia::core::ecs::ECS_CrabController::crab_idle_state() {
    if(!_accelerationIndex.is_success()) return;
    if(!_spriteFlipIndex.is_success()) return;
    if(!_spriteAnimationIndex.is_success()) return;
    if(!_colliderIndex.is_success()) return;
    if(!_velocityIndex.is_success()) return;
    
    ECS_Velocity& velocityComp = _parent->ref_unsafe(_velocityIndex);
    velocityComp.ref_velocity().x = 0.0f;

    const u64 random = rand();
    if(random % 10000 != 0) return;

    ECS_SpriteFlip& spriteFlipComp = _parent->ref_unsafe(_spriteFlipIndex);
    ECS_SpriteAnimation& spriteAnimationComp = _parent->ref_unsafe(_spriteAnimationIndex);
    spriteAnimationComp.set_animation("crab-run-animation");

    if(random % 2) {
        spriteFlipComp.set_vertical_flip(false);
        switch_state<ECS_CrabController>(&ECS_CrabController::crab_run_left_state);
    } else {
        spriteFlipComp.set_vertical_flip(true);
        switch_state<ECS_CrabController>(&ECS_CrabController::crab_run_right_state);
    }
}