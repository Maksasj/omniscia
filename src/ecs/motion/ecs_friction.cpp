#include "ecs_friction.h"

omniscia::core::ecs::ECS_Friction::ECS_Friction(const f32& friction) {
    _friction = friction;
}

omni::types::f32 omniscia::core::ecs::ECS_Friction::get_friction() const {
    return _friction;
}

omni::types::f32& omniscia::core::ecs::ECS_Friction::ref_friction() {
    return _friction;
}

void omniscia::core::ecs::ECS_Friction::set_friction(const f32& friction) {
    _friction = friction;
}
