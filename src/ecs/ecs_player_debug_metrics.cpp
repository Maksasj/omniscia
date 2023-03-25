#include "ecs_player_debug_metrics.h"

omniscia::core::ecs::ECS_PlayerDebugMetrics::ECS_PlayerDebugMetrics(Entity& parent) : _parent(parent) {
    ECS_PlayerDebugMetricsSystem::get_instance().bind_component(this);
};

void omniscia::core::ecs::ECS_PlayerDebugMetrics::time_sync() {
    ECS_PlayerDebugMetricsSystem::get_instance().bind_component(this);
}

void  omniscia::core::ecs::ECS_PlayerDebugMetrics::reindex(void* parent) {
    _parent = *(Entity*)parent;

    _posIndex = _parent.get().index<ECS_Positioned>();
}

void  omniscia::core::ecs::ECS_PlayerDebugMetrics::update() {
    if(!_posIndex.is_success()) return;

    ECS_Positioned& posComp = _parent.get().ref_unsafe(_posIndex);

    Vec3f& position = posComp.ref_pos();

    DebugUI::get_instance().get_metrics()._playerPos.x = position.x; 
    DebugUI::get_instance().get_metrics()._playerPos.y = position.y; 
}
