#include "ecs_2d_physics_rigidbody.h"

omniscia::core::ecs::ECS_2DPhysicsRigidbody::ECS_2DPhysicsRigidbody(Entity& parent) : _parent(parent) {
    ECS_2DPhysicsRigidbodySystem::get_instance().bind_component(this);
}

void omniscia::core::ecs::ECS_2DPhysicsRigidbody::reindex(void* parent) {
    _parent = *(Entity*)parent;
    
    _posIndex = _parent.get().index<ECS_Positioned>();
    _velocityIndex = _parent.get().index<ECS_Velocity>();
    _colliderIndex = _parent.get().index<ECS_MovableAABBCollider>();

    _frictionIndex = _parent.get().index<ECS_Friction>();
    _accelerationIndex = _parent.get().index<ECS_Acceleration>();
}

void omniscia::core::ecs::ECS_2DPhysicsRigidbody::time_sync() {
    ECS_2DPhysicsRigidbodySystem::get_instance().bind_component(this);
}

void omniscia::core::ecs::ECS_2DPhysicsRigidbody::update() {
    if(!_posIndex.is_success()) return;
    if(!_velocityIndex.is_success()) return;
    if(!_colliderIndex.is_success()) return;
    if(!_accelerationIndex.is_success()) return;
    if(!_colliderIndex.is_success()) return;

    f32 deltaTime = Time::get_instance().get_delta_time();

    ECS_Positioned& posComp = _parent.get().ref_unsafe(_posIndex);
    ECS_Velocity& velocityComp = _parent.get().ref_unsafe(_velocityIndex);
    ECS_Friction& frictionComp = _parent.get().ref_unsafe(_frictionIndex);
    ECS_Acceleration& accelerationComp = _parent.get().ref_unsafe(_accelerationIndex);
    ECS_MovableAABBCollider& colliderComp = _parent.get().ref_unsafe(_colliderIndex);

    Vec3f velocity = velocityComp.get_velocity();
    f32 friction = frictionComp.get_friction();

    accelerationComp.add_acceleration({velocity.x * friction, 0.0, 0.0});
    Vec3f acceleration = accelerationComp.get_acceleration();

    velocityComp.add_velocity({acceleration.x * deltaTime, 0.0f, 0.0f});
    velocityComp.clamp_velocity();

    velocity = velocityComp.get_velocity();

    posComp.move_pos({velocity.x * deltaTime - acceleration.x * 0.5f * (deltaTime * deltaTime), 0.0f, 0.0f});
}
