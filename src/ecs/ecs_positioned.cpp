#include "ecs_positioned.h"

omniscia::core::ecs::ECS_Positioned::ECS_Positioned() { 
    _pos = Vec3f{0.0f, 0.0f, 0.0f}; 
}

omniscia::core::ecs::ECS_Positioned::ECS_Positioned(const Vec3f& pos) {
    _pos = pos;
}

void omniscia::core::ecs::ECS_Positioned::reindex(void* parent) {

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
