#include "ecs/motion/ecs_box_collider_mesh.h"

omniscia::core::ecs::ECS_BoxColliderMesh::ECS_BoxColliderMesh(const Vec2f& xRanges, const Vec2f& yRanges) {
    _xRanges = xRanges;
    _yRanges = yRanges;
}

omni::types::Vec2f omniscia::core::ecs::ECS_BoxColliderMesh::get_x_collision_ranges() const {
    return _xRanges;
}

omni::types::Vec2f omniscia::core::ecs::ECS_BoxColliderMesh::get_y_collision_ranges() const {
    return _yRanges;
}
