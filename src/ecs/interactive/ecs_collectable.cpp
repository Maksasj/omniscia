#include "ecs_collectable.h"

#include "game.h"

omniscia::core::ecs::ECS_Collectable::ECS_Collectable() 
    : ECS_Interactive(1.0f, [](){}) {

};

void omniscia::core::ecs::ECS_Collectable::time_sync() {
    ECS_Interactive::time_sync();
}

void omniscia::core::ecs::ECS_Collectable::reindex(void* parent) {
    ECS_Interactive::reindex(parent);
}

void omniscia::core::ecs::ECS_Collectable::update() {
    if(!_triggerColliderIndex.is_success()) return;

    ECS_TriggerAABBCollider& colliderComp = ((Entity*)_parent)->ref_unsafe(_triggerColliderIndex);

    if(!colliderComp.is_triggered())
        return;

    Game::get_instance().start_cutscene("star_collection_cutscene");
    Game::get_instance().get_active_scene()->delete_static_entity_by_uuid(_parent->get_uuid());
    
    DebugInfo::get_instance().get_metrics()._systemInterupt = true;
}
