#include "ecs_interactive_collision.h"

omniscia::core::ecs::ECS_InteractiveCollision::ECS_InteractiveCollision(const f32& cooldown, const std::function<void(void)>& lambda) : ECS_Interactive(cooldown, lambda) {

};

void omniscia::core::ecs::ECS_InteractiveCollision::update() {
    if(!_enabled) return;

    if(!_triggerColliderIndex.is_success())
        return;

    ECS_TriggerAABBCollider& colliderComp = _parent->ref_unsafe(_triggerColliderIndex);

    if(!colliderComp.is_triggered()) {
        _timer = 0.0f;
        return;
    }

    auto dt = Time::get_instance().get_delta_time();
    _timer += dt;
    
    if(_timer < _cooldown) 
        return;

    _lambda();

    _timer = 0.0f;
}
