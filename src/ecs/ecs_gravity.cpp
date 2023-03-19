#include "ecs_gravity.h"

omniscia::core::ecs::ECS_Gravity::ECS_Gravity(Entity& parent) : _parent(parent) {
    ECS_GravitySystem::get_instance().bind_component(this);
};

void omniscia::core::ecs::ECS_Gravity::time_sync() {
    ECS_GravitySystem::get_instance().bind_component(this);
}

void  omniscia::core::ecs::ECS_Gravity::reindex(void* parent) {
    _parent = *(Entity*)parent;

    velocityIndex = _parent.get().index<ECS_Velocity>();
}

void  omniscia::core::ecs::ECS_Gravity::update() {
    ECS_Velocity &velocityComp = _parent.get().ref_unsafe(velocityIndex);
}
