#include "ecs_player_jump.h"

omniscia::core::ecs::ECS_PlayerJump::ECS_PlayerJump(Entity& parent) : _parent(parent) {
    ECS_PlayerJumpSystem::get_instance().bind_component(this);
};

void omniscia::core::ecs::ECS_PlayerJump::time_sync() {
    ECS_PlayerJumpSystem::get_instance().bind_component(this);
}

void omniscia::core::ecs::ECS_PlayerJump::reindex(void* parent) {
    _parent = *(Entity*)parent;

    velocityIndex = _parent.get().index<ECS_Velocity>();
    movableAABBColliderIndex = _parent.get().index<ECS_MovableAABBCollider>();
}

void omniscia::core::ecs::ECS_PlayerJump::update() {
    if(!movableAABBColliderIndex.is_success()) return;
    if(!velocityIndex.is_success()) return;

    ECS_MovableAABBCollider& movableAABBColliderComp = _parent.get().ref_unsafe(movableAABBColliderIndex);
    ECS_Velocity &velocityComp = _parent.get().ref_unsafe(velocityIndex);

    Vec3f& velocity = velocityComp.ref_velocity();

    if(!movableAABBColliderComp.is_colliding_by_y()) return;

    if(Controls::get(PlayerController::JUMP)) {
        velocity.y = 0.04f;
    }
}
