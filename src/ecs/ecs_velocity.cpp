#include "ecs_velocity.h"

omniscia::core::ecs::ECS_Velocity::ECS_Velocity() { 
    _vel = Vec3f{0.0f, 0.0f, 0.0f}; 
    _maxVelocity = 1.0;
    _minVelocity = -1.0;
}

omniscia::core::ecs::ECS_Velocity::ECS_Velocity(const Vec3f& vel) {
    _vel = vel;
    _maxVelocity = 0.0;
    _minVelocity = 0.0;
}

omniscia::core::ecs::ECS_Velocity::ECS_Velocity(const Vec3f& vel, const f32& maxVelocity) {
    _vel = vel;
    _maxVelocity = maxVelocity;
    _minVelocity = 0.0;
}

omniscia::core::ecs::ECS_Velocity::ECS_Velocity(const Vec3f& vel, const f32& maxVelocity, const f32& minVelocity) {
    _vel = vel;
    _maxVelocity = maxVelocity;
    _minVelocity = minVelocity;
}

omniscia::core::ecs::ECS_Velocity::ECS_Velocity(const f32& maxVelocity, const f32& minVelocity) { 
    _vel = Vec3f{0.0f, 0.0f, 0.0f}; 
    _maxVelocity = maxVelocity;
    _minVelocity = minVelocity;
}

void omniscia::core::ecs::ECS_Velocity::reindex(void* parent) {

}

omniscia::core::Vec3f omniscia::core::ecs::ECS_Velocity::get_velocity() const {
    return _vel;
}

void omniscia::core::ecs::ECS_Velocity::add_velocity(Vec3f force) {
    _vel += force;
}

void omniscia::core::ecs::ECS_Velocity::set_velocity(Vec3f velocity) {
    _vel = velocity;
}
