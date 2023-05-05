#include "ecs_scaled.h"

omniscia::core::ecs::ECS_Scaled::ECS_Scaled(const f32& scaleX, const f32& scaleY) { _scale = Vec2f{scaleX, scaleY}; }
omniscia::core::ecs::ECS_Scaled::ECS_Scaled(const Vec2f& scale) { _scale = scale; }

omni::types::Vec2f omniscia::core::ecs::ECS_Scaled::get_scale() const {
    return _scale;
}

void omniscia::core::ecs::ECS_Scaled::set_scale(const Vec2f& newScale) {
    _scale = newScale;
}
