#include "ecs_velocity.h"

omniscia::core::ecs::ECS_Velocity::ECS_Velocity(const f32& velX, const f32& velY, const f32& velZ) {
    _vel = Vec3f{velX, velY, velZ};
    _velocityRangesX = Vec2f{1.0, -1.0};
    _velocityRangesY = Vec2f{1.0, -1.0};
}

omniscia::core::ecs::ECS_Velocity::ECS_Velocity(const Vec3f& vel, const Vec2f& velocityRangesX) {
    _vel = vel;
    _velocityRangesX = velocityRangesX;
    _velocityRangesY = Vec2f{1.0, -1.0};
}

omniscia::core::ecs::ECS_Velocity::ECS_Velocity(const Vec3f& vel, const Vec2f& velocityRangesX, const Vec2f& velocityRangesY) {
    _vel = vel;
    _velocityRangesX = velocityRangesX;
    _velocityRangesY = velocityRangesY;
}

omniscia::core::ecs::ECS_Velocity::ECS_Velocity(const Vec2f& velocityRangesX, const Vec2f& velocityRangesY) { 
    _vel = Vec3f{0.0f, 0.0f, 0.0f}; 
    
    _velocityRangesX = velocityRangesX;
    _velocityRangesY = velocityRangesY;
}

void omniscia::core::ecs::ECS_Velocity::reindex(void* parent) {

}

omniscia::core::Vec3f omniscia::core::ecs::ECS_Velocity::get_velocity() const {
    return _vel;
}

omniscia::core::Vec3f& omniscia::core::ecs::ECS_Velocity::ref_velocity() {
    return _vel;
}

void omniscia::core::ecs::ECS_Velocity::add_velocity(Vec3f force) {
    _vel += force;
}

void omniscia::core::ecs::ECS_Velocity::set_velocity(Vec3f velocity) {
    _vel = velocity;
}
