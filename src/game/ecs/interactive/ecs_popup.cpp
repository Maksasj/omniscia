#include "ecs/interactive/ecs_popup.h"

omniscia::core::ecs::ECS_Popup::ECS_Popup(
    const f32& visibilityDistance, 
    const f32& scale,
    const Vec2f& offset,
    const std::string& textureId, 
    const std::string& popupAnimation, 
    const f32& cooldown, 
    const std::function<void(void)>& lambda) 
    : ECS_Interactive(cooldown, lambda), _renderer(textureId, 10, popupAnimation) {
    
    _offset = offset;

    _renderer.set_scale(scale);

    _visibilityDistance = visibilityDistance;
    _animationId = popupAnimation;
};

void omniscia::core::ecs::ECS_Popup::time_sync() {
    ECS_Interactive::time_sync();
    _renderer.time_sync();
}

void omniscia::core::ecs::ECS_Popup::reindex(void* parent) {
    ECS_Interactive::reindex(parent);
    
    _renderer.reindex(parent);

    _posIndex = _parent->index<ECS_Positioned>();
}

void omniscia::core::ecs::ECS_Popup::update() {
    if(!_posIndex.is_success()) return;

    auto time = Time::get_instance().get_time();
    auto dt = Time::get_instance().get_delta_time();
    
    Vec2f playerPos = DebugInfo::get_instance().get_metrics()._playerPos;
    ECS_Positioned& posComp = _parent->ref_unsafe(_posIndex);
    Vec2f pos = posComp.get_pos();

    Vec2f delta = playerPos - pos;
    if(delta.x*delta.x + delta.y*delta.y < _visibilityDistance) {
        _renderer.enable();

        auto transparency = _renderer.get_transparency(); 

        _renderer.set_transparency(transparency + dt * 0.003f);
        _renderer.clamp_transparency();
    } else {
        auto transparency = _renderer.get_transparency(); 

        _renderer.set_transparency(transparency - dt * 0.003f);
        _renderer.clamp_transparency();

        if(_renderer.get_transparency() < 0.05f) 
            _renderer.disable();

        _timer = 0.0f;
    }

    _renderer.set_offset(Vec2f{_offset.x + 0.0f, _offset.y + 0.1f + 0.02f * (f32)sin(time)});
    
    if(!_triggerColliderIndex.is_success())
        return;

    if(!Controls::get_instance().get(PlayerController::INTERACT)) {
        _timer = 0.0f;
        _renderer.set_frame(round(6u * (_timer / _cooldown)));
        return;
    }

    ECS_TriggerAABBCollider& colliderComp = ((Entity*)_parent)->ref_unsafe(_triggerColliderIndex);

    if(!colliderComp.is_triggered()) {
        _timer = 0.0f;
        _renderer.set_frame(round(6u * (_timer / _cooldown)));
        return;
    }

    _timer += dt;
    
    if(_timer < _cooldown) {
        _renderer.set_frame(round(6u * (_timer / _cooldown)));
        return;
    }

    _renderer.set_frame(6u);

    _lambda();

    _timer = 0.0f;
}
