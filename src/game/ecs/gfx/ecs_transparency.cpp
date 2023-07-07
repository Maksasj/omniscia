#include "ecs_transparency.h"

omniscia::core::ecs::ECS_Transparency::ECS_Transparency(const f32& transparency) {
    _transparency = transparency;
}

omni::types::f32 omniscia::core::ecs::ECS_Transparency::get_transparency() const {
    return _transparency;
}

omni::types::f32& omniscia::core::ecs::ECS_Transparency::ref_transparency() {
    return _transparency;
}

void omniscia::core::ecs::ECS_Transparency::set_transparency(const f32& transparency) {
    _transparency = transparency;
}
    
