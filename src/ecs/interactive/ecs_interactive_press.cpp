#include "ecs_interactive_press.h"

omniscia::core::ecs::ECS_InteractivePress::ECS_InteractivePress(const f32& cooldown, const std::function<void(void)>& lambda) : ECS_Interactive(cooldown, lambda){

};

void omniscia::core::ecs::ECS_InteractivePress::update() {
    if(!_enabled) return;

    if(!_triggerColliderIndex.is_success())
        return;

    if(!Controls::get_instance().get(PlayerController::INTERACT))
        return;

    ECS_TriggerAABBCollider& colliderComp = ((Entity*)_parent)->ref_unsafe(_triggerColliderIndex);

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
