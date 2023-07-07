#include "ecs_interactive.h"

omniscia::core::ecs::ECS_Interactive::ECS_Interactive(const f32& cooldown, const std::function<void(void)>& lambda) {
    _cooldown = cooldown;
    _lambda = lambda;
    _timer = 0;

    ECS_InteractiveSystem::get_instance().bind_component(this);
};

void omniscia::core::ecs::ECS_Interactive::time_sync() {
    ECS_InteractiveSystem::get_instance().bind_component(this);
}

void omniscia::core::ecs::ECS_Interactive::reindex(void* parent) {
    _parent = (Entity*)parent;

    _triggerColliderIndex = _parent->index<ECS_TriggerAABBCollider>(); 
}
