#include "ecs_velocity_slowdown.h"

omniscia::core::ecs::ECS_VelocitySlowdown::ECS_VelocitySlowdown(Entity& parent) : _parent(parent) {
    ECS_VelocitySlowdownSystem::get_instance().bind_component(this);
};

void omniscia::core::ecs::ECS_VelocitySlowdown::time_sync() {
    ECS_VelocitySlowdownSystem::get_instance().bind_component(this);
}

void  omniscia::core::ecs::ECS_VelocitySlowdown::reindex(void* parent) {
    _parent = *(Entity*)parent;

    velocityIndex = _parent.get().index<ECS_Velocity>();
}

void  omniscia::core::ecs::ECS_VelocitySlowdown::update() {
    ECS_Velocity &velocityComp = _parent.get().ref_unsafe(velocityIndex);
    
    Vec3f velocity = velocityComp.get_velocity();

    velocityComp.set_velocity({velocity.x*0.98f, velocity.y*0.98f, velocity.z*0.98f});
}
