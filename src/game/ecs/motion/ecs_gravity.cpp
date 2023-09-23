#include "ecs/motion/ecs_gravity.h"

omniscia::core::ecs::ECS_Gravity::ECS_Gravity() {
    _gravitationalAcceleration = 0.00001f;

    ECS_GravitySystem::get_instance().bind_component(this);
};

void omniscia::core::ecs::ECS_Gravity::time_sync() {
    ECS_GravitySystem::get_instance().bind_component(this);
}

void omniscia::core::ecs::ECS_Gravity::reindex(void* parent) {
    _parent = (Entity*)parent;

    velocityIndex = _parent->index<ECS_Velocity>();
    accelerationIndex = _parent->index<ECS_Acceleration>();
}

void omniscia::core::ecs::ECS_Gravity::update() {
    if(!_enabled) return;

    if(!velocityIndex.is_success()) return;
    if(!accelerationIndex.is_success()) return;

    ECS_Velocity &velocityComp = _parent->ref_unsafe(velocityIndex);
    ECS_Acceleration &accelerationComp = _parent->ref_unsafe(accelerationIndex);

    Vec3f& velocity = velocityComp.ref_velocity();
    Vec3f& acceleration = accelerationComp.ref_acceleration();

    f32 dt = Time::get_instance().get_delta_time();

    velocity.y -= _gravitationalAcceleration * dt;
}
