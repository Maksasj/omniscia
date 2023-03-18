#include "ecs_2d_physics_rigidbody.h"

omniscia::core::ecs::ECS_2DPhysicsRigidbody::ECS_2DPhysicsRigidbody(Entity& parent) : _parent(parent) {
    ECS_2DPhysicsRigidbodySystem::get_instance().bind_component(this);
}

void omniscia::core::ecs::ECS_2DPhysicsRigidbody::reindex(void* parent) {
    _parent = *(Entity*)parent;
    
    _posIndex = _parent.get().index<ECS_Positioned>();
    _velocityIndex = _parent.get().index<ECS_Velocity>();
    _colliderIndex = _parent.get().index<ECS_MovableAABBCollider>();
}

void omniscia::core::ecs::ECS_2DPhysicsRigidbody::time_sync() {
    ECS_2DPhysicsRigidbodySystem::get_instance().bind_component(this);
}

void omniscia::core::ecs::ECS_2DPhysicsRigidbody::update() {
    if(!_posIndex.is_success()) return;
    if(!_velocityIndex.is_success()) return;
    if(!_colliderIndex.is_success()) return;

    ECS_Positioned& posComp = _parent.get().ref_unsafe(_posIndex);
    ECS_Velocity& velocityComp = _parent.get().ref_unsafe(_velocityIndex);
    ECS_MovableAABBCollider& colliderComp = _parent.get().ref_unsafe(_colliderIndex);

    Vec3 velocity = velocityComp.get_velocity();
    Vec3 possition = posComp.get_pos();

    if(!colliderComp.get_colliding_with_by_x()) { 
        posComp.move_pos({velocity.x, 0.0, 0.0}); 
    } else {
        //posComp.set_pos({colliderComp.get_collision_point_by_x().x, possition.y, possition.z});
        velocityComp.set_velocity({0.0, velocity.x, velocity.y});
    }

    if(!colliderComp.get_colliding_with_by_y()) { 
        posComp.move_pos({0.0, velocity.y, 0.0});
    } else {
        //posComp.set_pos({possition.x, colliderComp.get_collision_point_by_y().y, possition.z});
        velocityComp.set_velocity({velocity.x, 0.0, velocity.y});
    } 
}
