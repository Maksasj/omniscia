#include "ecs_player_collector_controller.h"

#include "game.h"

omniscia::core::ecs::ECS_PlayerCollectorController::ECS_PlayerCollectorController() : ECS_StateMachineBase() {
    _collected = 0;
    
    ECS_StateMachineBaseSystem::get_instance().bind_component(this);
    switch_state<ECS_PlayerCollectorController>(&ECS_PlayerCollectorController::player_collector_state);
};

void omniscia::core::ecs::ECS_PlayerCollectorController::time_sync() {
    ECS_StateMachineBaseSystem::get_instance().bind_component(this);
}

void omniscia::core::ecs::ECS_PlayerCollectorController::reindex(void* parent) {
    _parent = (Entity*) parent;
}

void omniscia::core::ecs::ECS_PlayerCollectorController::player_collector_state() {

}

void omniscia::core::ecs::ECS_PlayerCollectorController::collect() {
    ++_collected;

    auto scene = Game::get_instance().get_active_scene();

    if(scene == nullptr) 
        return;
    
    std::shared_ptr<Entity> entityPtr= scene->find_static_entity_by_prototype<CollectedText>();
    if(entityPtr == nullptr) return;

    ECS_Index<ECS_TextRenderer> textRendererIndex = entityPtr->index<ECS_TextRenderer>();
    
    if(!textRendererIndex.is_success()) 
        return;

    ECS_TextRenderer& comp = entityPtr->ref_unsafe(textRendererIndex);

    const std::string newScore = std::string("x") + std::to_string(_collected);  

    comp.set_text_to_render(newScore, 0.31f, 0.0f, 3u);    
}
