#include "ecs_state_machine_base.h"

omniscia::core::ecs::ECS_StateMachineBase::ECS_StateMachineBase() {
    ECS_StateMachineBaseSystem::get_instance().bind_component(this);
};

void omniscia::core::ecs::ECS_StateMachineBase::time_sync() {
    ECS_StateMachineBaseSystem::get_instance().bind_component(this);
}

void omniscia::core::ecs::ECS_StateMachineBase::reindex(void* parent) {
    _parent = (Entity*) parent;
}

void omniscia::core::ecs::ECS_StateMachineBase::update() {
    if(_activeState == nullptr) return;

    (this->*_activeState)();
}
