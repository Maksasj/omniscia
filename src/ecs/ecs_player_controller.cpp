#include "ecs_player_controller.h"

omniscia::core::ecs::ECS_PlayerController::ECS_PlayerController(Entity& parent) : _parent(parent) {
    ECS_PlayerControllerSystem::get_instance().bind_component(this);
};

void omniscia::core::ecs::ECS_PlayerController::time_sync() {
    ECS_PlayerControllerSystem::get_instance().bind_component(this);
}
