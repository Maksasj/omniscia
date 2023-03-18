#include "ecs_scaled.h"

omniscia::core::ecs::ECS_Scaled::ECS_Scaled() { _scale = Vec2f{1.0f, 1.0f}; }
omniscia::core::ecs::ECS_Scaled::ECS_Scaled(const Entity& entity) { _scale = Vec2f{1.0f, 1.0f}; }
omniscia::core::ecs::ECS_Scaled::ECS_Scaled(const Vec2f& scale) { _scale = scale; }
omniscia::core::ecs::ECS_Scaled::ECS_Scaled(const Vec2f& scale, const Entity& entity) { _scale = scale; }

void omniscia::core::ecs::ECS_Scaled::reindex(void* parent) {

}

omniscia::core::Vec2f omniscia::core::ecs::ECS_Scaled::get_scale() const {
    return _scale;
}

void omniscia::core::ecs::ECS_Scaled::set_scale(const Vec2f& newScale) {
    _scale = newScale;
}
