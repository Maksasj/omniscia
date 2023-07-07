#include "ecs_physics_positioned.h"

omniscia::core::ecs::ECS_PhysicsPositioned::ECS_PhysicsPositioned() {
    _newPosition = Vec3f{0.0f, 0.0f, 0.0f};
    _oldPosition = Vec3f{0.0f, 0.0f, 0.0f};
}

omni::types::Vec3f omniscia::core::ecs::ECS_PhysicsPositioned::get_old_position() const {
    return _oldPosition;
}

omni::types::Vec3f omniscia::core::ecs::ECS_PhysicsPositioned::get_new_position() const {
    return _newPosition;
}

void omniscia::core::ecs::ECS_PhysicsPositioned::set_old_position(const Vec3f& value) {
    _oldPosition = value;
}

void omniscia::core::ecs::ECS_PhysicsPositioned::set_new_position(const Vec3f& value) {
    _newPosition = value;
}
