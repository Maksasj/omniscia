#include "ecs/controllers/ecs_star_controller.h"

omniscia::core::ecs::ECS_StarController::ECS_StarController() : ECS_StateMachineBase() {
    ECS_StateMachineBaseSystem::get_instance().bind_component(this);
    switch_state<ECS_StarController>(&ECS_StarController::star_chase_state);
};

void omniscia::core::ecs::ECS_StarController::time_sync() {
    ECS_StateMachineBaseSystem::get_instance().bind_component(this);
}

void omniscia::core::ecs::ECS_StarController::reindex(void* parent) {
    _parent = (Entity*) parent;

    _accelerationIndex = _parent->index<ECS_Acceleration>();
    _positionIndex = _parent->index<ECS_Positioned>();
    _velocityIndex = _parent->index<ECS_Velocity>();
}

void omniscia::core::ecs::ECS_StarController::star_chase_state() {
    if(!_accelerationIndex.is_success()) return;
    if(!_positionIndex.is_success()) return;
    if(!_velocityIndex.is_success()) return;

    ECS_Acceleration &accelerationComp = _parent->ref_unsafe(_accelerationIndex);
    ECS_Positioned &positionComp = _parent->ref_unsafe(_positionIndex);
    ECS_Velocity &velocityComp = _parent->ref_unsafe(_velocityIndex);

    Vec3f& acceleration = accelerationComp.ref_acceleration();
    Vec3f& velocity = velocityComp.ref_velocity();
    Vec3f& position = positionComp.ref_pos();

    const Vec2f& playerPos = DebugInfo::get_instance().get_metrics()._playerPos;

    const Vec2f delta = Vec2f(position.x - playerPos.x, position.y - playerPos.y);

    if(delta.x * delta.x + delta.y * delta.y > 0.25f) {
        velocity.x = 0;
        velocity.y = 0;
        
        return;
    }

    if(delta.x < 0)
        acceleration.x = 0.00001f;
    else
        acceleration.x = -0.00001f;

    if(delta.y < 0)
        acceleration.y = 0.00001f;
    else
        acceleration.y = -0.00001f;
}
