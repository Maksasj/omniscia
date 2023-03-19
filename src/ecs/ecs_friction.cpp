#include "ecs_friction.h"

omniscia::core::ecs::ECS_Friction::ECS_Friction() { 
    _friction = 0.0;
}

omniscia::core::ecs::ECS_Friction::ECS_Friction(const f32& friction) {
    _friction = friction;
}

void omniscia::core::ecs::ECS_Friction::reindex(void* parent) {

}

f32 omniscia::core::ecs::ECS_Friction::get_friction() const {
    return _friction;
}

void omniscia::core::ecs::ECS_Friction::set_friction(const f32& friction) {
    _friction = friction;
}
