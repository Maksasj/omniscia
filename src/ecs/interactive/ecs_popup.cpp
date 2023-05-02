#include "ecs_popup.h"

omniscia::core::ecs::ECS_Popup::ECS_Popup(const f32& visibilityDistance, const std::string& popupAnimation, const f32& cooldown, const std::function<void(void)>& lambda) 
    : ECS_Interactive(cooldown, lambda), _renderer("popups", 1, popupAnimation) {
    
    _visibilityDistance = visibilityDistance;
    _animationId = popupAnimation;
};

void omniscia::core::ecs::ECS_Popup::time_sync() {
    ECS_Interactive::time_sync();
    _renderer.time_sync();
}

void omniscia::core::ecs::ECS_Popup::reindex(void* parent) {
    _parent = (Entity*) parent;
    
    ECS_Interactive::reindex(parent);
    _renderer.reindex(parent);

    _posIndex = _parent->index<ECS_Positioned>();
}

void omniscia::core::ecs::ECS_Popup::update() {
    if(!_posIndex.is_success()) return;
    
    Vec2f playerPos = DebugUI::get_instance().get_metrics()._playerPos;
    ECS_Positioned& posComp = _parent->ref_unsafe(_posIndex);
    Vec2f pos = posComp.get_pos();

    Vec2f delta = playerPos - pos;
    if(delta.x*delta.x + delta.y*delta.y < _visibilityDistance)
        _renderer.enable();
    else
        _renderer.disable();

    auto time = Time::get_instance().get_time();
    _renderer.set_offset(Vec2f{0.0f, 0.1f + 0.02f * (f32)sin(time)});
    
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
    
    if(_timer < _cooldown) {
        _renderer.set_frame(6u * (_timer / _cooldown));
        return;
    } 

    _renderer.set_frame(6u);

    _lambda();

    _timer = 0.0f;
}
