#include "spawn_entity_cutscene_event.h"
#include "game.h"

omniscia::core::CE_SpawnEntityEvent::CE_SpawnEntityEvent() {

}

omniscia::core::CE_SpawnEntityEvent::CE_SpawnEntityEvent(const CE_SpawnEntityEvent&) {

}

void omniscia::core::CE_SpawnEntityEvent::operator=(const CE_SpawnEntityEvent&) {

}

omniscia::core::CE_SpawnEntityEvent::CE_SpawnEntityEvent(const CE_SpawnEntityProp& data) : CE_SpawnEntityProp(data), CE_Event(*(CE_Prop*)&data) {

}

void omniscia::core::CE_SpawnEntityEvent::execute() {
    auto scene = Game::get_instance().get_active_scene();

    if(scene == nullptr) 
        return;
    
    _summonLambda(scene);

    scene->time_sync();
}
