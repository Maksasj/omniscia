#include "ecs_2d_physics_rigidbody.h"

omniscia::core::ecs::ECS_2DPhysicsRigidbody::ECS_2DPhysicsRigidbody() {
    ECS_2DPhysicsRigidbodySystem::get_instance().bind_component(this);
}

void omniscia::core::ecs::ECS_2DPhysicsRigidbody::reindex(void* parent) {
    _parent = (Entity*)parent;
    
    _posIndex = _parent->index<ECS_Positioned>();
    _velocityIndex = _parent->index<ECS_Velocity>();
    _colliderIndex = _parent->index<ECS_MovableAABBCollider>();

    _frictionIndex = _parent->index<ECS_Friction>();
    _accelerationIndex = _parent->index<ECS_Acceleration>();
    _physicsPositionedIndex = _parent->index<ECS_PhysicsPositioned>();
}

void omniscia::core::ecs::ECS_2DPhysicsRigidbody::time_sync() {
    ECS_2DPhysicsRigidbodySystem::get_instance().bind_component(this);
}

void omniscia::core::ecs::ECS_2DPhysicsRigidbody::update() {
    if(!_posIndex.is_success()) return;
    if(!_velocityIndex.is_success()) return;
    if(!_frictionIndex.is_success()) return;
    if(!_accelerationIndex.is_success()) return;

    ECS_Positioned& posComp = _parent->ref_unsafe(_posIndex);
    ECS_Velocity& velocityComp = _parent->ref_unsafe(_velocityIndex);
    ECS_Friction& frictionComp = _parent->ref_unsafe(_frictionIndex);
    ECS_Acceleration& accelerationComp = _parent->ref_unsafe(_accelerationIndex);
    ECS_PhysicsPositioned& physicsPositioneComp = _parent->ref_unsafe(_physicsPositionedIndex);

    Vec3f position = posComp.ref_pos();
    Vec3f& velocity = velocityComp.ref_velocity();
    f32& friction = frictionComp.ref_friction();
    Vec3f& acceleration = accelerationComp.ref_acceleration();

    f32 dt = Time::get_instance().get_delta_time();

    physicsPositioneComp.set_old_position(position);

    acceleration.x += velocity.x * friction;
    velocity.x += acceleration.x * dt;

    velocityComp.clamp_velocity();

    position.x += velocity.x * dt + acceleration.x * 0.5 * dt * dt;
    position.y += velocity.y * dt + acceleration.y * 0.5 * dt * dt;

    physicsPositioneComp.set_new_position(position);
}

void omniscia::core::ecs::ECS_2DPhysicsRigidbody::late_update() {
    if(!_posIndex.is_success()) return;
    if(!_colliderIndex.is_success()) return;
    if(!_physicsPositionedIndex.is_success()) return;

    ECS_Positioned& posComp = _parent->ref_unsafe(_posIndex);
    ECS_MovableAABBCollider& colliderComp = _parent->ref_unsafe(_colliderIndex);
    ECS_PhysicsPositioned& physicsPosComp = _parent->ref_unsafe(_physicsPositionedIndex);

    Vec3f& position = posComp.ref_pos();

    if(!colliderComp.is_colliding_by_x()) {
        position.x = physicsPosComp.get_new_position().x;
    }

    if(!colliderComp.is_colliding_by_y()) {
        position.y = physicsPosComp.get_new_position().y;
    }
}
