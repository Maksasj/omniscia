#include "ecs_deadly.h"

#include "game.h"

omniscia::core::ecs::ECS_Deadly::ECS_Deadly() : ECS_TriggerAABBCollider(CollisionMask_Deadly, CollisionMask_Player) {
    ECS_DeadlySystem::get_instance().bind_component(this);
};

void omniscia::core::ecs::ECS_Deadly::time_sync() {
    ECS_AABBCollider::time_sync();
    ECS_DeadlySystem::get_instance().bind_component(this);
}

void omniscia::core::ecs::ECS_Deadly::update() {
    if(!_enabled) return;

    if(!is_triggered()) return;

    Game::get_instance().start_cutscene("death_cutscene");    
}