#include "scene/cutscene/events/entity/destroy_entity_cutscene_event.h"
#include "game.h"

omniscia::core::CE_DestroyEntityEvent::CE_DestroyEntityEvent() {

}

omniscia::core::CE_DestroyEntityEvent::CE_DestroyEntityEvent(const CE_DestroyEntityEvent&) {

}

void omniscia::core::CE_DestroyEntityEvent::operator=(const CE_DestroyEntityEvent&) {

}

omniscia::core::CE_DestroyEntityEvent::CE_DestroyEntityEvent(const CE_DestroyEntityProp& data) : CE_DestroyEntityProp(data), CE_Event(*(CE_Prop*)&data) {

}

void omniscia::core::CE_DestroyEntityEvent::execute() {
    CutsceneDataPoolType* ptrParrentCutsceneDataPool = get_cutscene_data_pool();
    if(ptrParrentCutsceneDataPool == nullptr) 
        return;
    
    auto scene = Game::get_instance().get_active_scene();

    if(scene == nullptr) 
        return;
    
    CutsceneDataPoolType& _dataPool = *ptrParrentCutsceneDataPool;
    UUID* entityUUID = (UUID*)_dataPool[_entityTmpName].get();

    scene->delete_static_entity_by_uuid(*entityUUID);
    scene->time_sync();
}
