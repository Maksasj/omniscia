#include "ecs_positioned.h"

omniscia::core::ecs::ECS_Positioned::ECS_Positioned(const f32& x, const f32& y, const f32& z) { 
    _pos = Vec3f{x, y, z}; 
}

omniscia::core::ecs::ECS_Positioned::ECS_Positioned(const Vec3f& pos) {
    _pos = pos;
}

omniscia::core::Vec3f omniscia::core::ecs::ECS_Positioned::get_pos() const {
    return _pos;
}

omniscia::core::Vec3f& omniscia::core::ecs::ECS_Positioned::ref_pos() {
    return _pos;
}

void omniscia::core::ecs::ECS_Positioned::set_pos(const Vec3f& newPos) {
    _pos = newPos;
}

void omniscia::core::ecs::ECS_Positioned::move_pos(const Vec3f& movedPos) {
    _pos += movedPos;
}

void omniscia::core::ecs::ECS_Positioned::_type_query(void* query) {
    DebugFieldQuery::debug_component_edit_query<ECS_Positioned>(*this);
}