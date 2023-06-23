#include "ecs_player_debug_metrics.h"

omniscia::core::ecs::ECS_PlayerDebugMetrics::ECS_PlayerDebugMetrics() {
    ECS_PlayerDebugMetricsSystem::get_instance().bind_component(this);
};

void omniscia::core::ecs::ECS_PlayerDebugMetrics::time_sync() {
    ECS_PlayerDebugMetricsSystem::get_instance().bind_component(this);
}

void  omniscia::core::ecs::ECS_PlayerDebugMetrics::reindex(void* parent) {
    _parent = (Entity*)parent;

    _posIndex = _parent->index<ECS_Positioned>();
}

void  omniscia::core::ecs::ECS_PlayerDebugMetrics::update() {
    if(!_posIndex.is_success()) return;

    ECS_Positioned& posComp = _parent->ref_unsafe(_posIndex);

    Vec3f& position = posComp.ref_pos();

    DebugInfo::get_instance().get_metrics()._playerPos.x = position.x; 
    DebugInfo::get_instance().get_metrics()._playerPos.y = position.y; 
}
