#include "ecs_player_controller.h"

omniscia::core::ecs::ECS_PlayerController::ECS_PlayerController(Entity& parent) : _parent(parent) {
    ECS_PlayerControllerSystem::get_instance().bind_component(this);
};

void omniscia::core::ecs::ECS_PlayerController::time_sync() {
    ECS_PlayerControllerSystem::get_instance().bind_component(this);
}

void  omniscia::core::ecs::ECS_PlayerController::reindex(void* parent) {
    _parent = *(Entity*)parent;

    posIndex = _parent.get().index<ECS_Positioned>();
}

void  omniscia::core::ecs::ECS_PlayerController::control() {
    ECS_Positioned &position = _parent.get().ref_unsafe(posIndex);

    if(Controls::get(PlayerController::JUMP))
        position.move_pos(Vec3f{0.0f, 0.001f, 0.0f});
    
    if(Controls::get(PlayerController::DOWN))
        position.move_pos(Vec3f{0.0f, -0.001f, 0.0f});
        
    if(Controls::get(PlayerController::LEFT))
        position.move_pos(Vec3f{-0.001f, 0.0f, 0.0f});
    
    if(Controls::get(PlayerController::RIGHT))
        position.move_pos(Vec3f{0.001f, 0.0f, 0.0f});
}
