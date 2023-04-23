#include "ecs_button.h"

omniscia::core::ecs::ECS_Button::ECS_Button(const std::function<void(void)> clickLambda) {
    ECS_ButtonSystem::get_instance().bind_component(this);

    _clickLambda = clickLambda;
};

omniscia::core::ecs::ECS_Button::ECS_Button(const std::function<void(void)> clickLambda, const std::function<void(void)> hoverLambda) {
    ECS_ButtonSystem::get_instance().bind_component(this);

    _clickLambda = clickLambda;
    _hoverLambda = hoverLambda;
};

void omniscia::core::ecs::ECS_Button::time_sync() {
    ECS_ButtonSystem::get_instance().bind_component(this);
}

void  omniscia::core::ecs::ECS_Button::reindex(void* parent) {
    _parent = (Entity*)parent;

    _posIndex = _parent->index<ECS_Positioned>();
    _scaleIndex = _parent->index<ECS_Scaled>();
    _colliderIndex = _parent->index<ECS_BoxColliderMesh>();
}

void omniscia::core::ecs::ECS_Button::update() {
    if(!_posIndex.is_success()) return;
    if(!_scaleIndex.is_success()) return;
    if(!_colliderIndex.is_success()) return;

    ECS_Positioned& posComp =_parent->ref_unsafe(_posIndex); 
    ECS_Scaled& scaledComp =_parent->ref_unsafe(_scaleIndex); 
    ECS_BoxColliderMesh& colliderComp =_parent->ref_unsafe(_colliderIndex); 

    auto xRanges = colliderComp.get_x_collision_ranges();
    auto yRanges = colliderComp.get_y_collision_ranges();
    auto pos = posComp.get_pos();
    auto scale = scaledComp.get_scale();

    auto mouse = Controls::get_instance().get_mouse();

    if((
        mouse.x >= pos.x - scale.x * xRanges.x &&
        mouse.x <= pos.x + scale.x * xRanges.y &&
        mouse.y >= pos.y - scale.y * yRanges.x &&
        mouse.y <= pos.y + scale.y * yRanges.y
    )) {
        _hoverLambda();

        if(Controls::get_instance().get(MouseController::LEFT_CLICK)) {
            _clickLambda();

            /* Resolve this cringe */
            DebugUI::get_instance().get_metrics()._isTimeJump = true;
        }
    }
}
