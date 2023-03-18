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
    
    Vec3f velocity = velocityComp.get_velocity();

    constexpr f32 epsilon = 0.01;

    if((velocity.y > 0.0)) {
        if(velocity.y < epsilon) {
            velocityComp.set_velocity({velocity.x, -0.001, velocity.z});
        } else {
            velocityComp.set_velocity({velocity.x, velocity.y * 0.98f, velocity.z});
        }
    } else if(velocity.y < 0.0){
        velocityComp.set_velocity({velocity.x, velocity.y * 1.01f, velocity.z});
    } else {
        velocityComp.set_velocity({velocity.x, -0.001, velocity.z});
    }

    velocityComp.clamp_velocity();
}
