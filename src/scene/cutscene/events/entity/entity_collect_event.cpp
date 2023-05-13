#include "entity_collect_event.h"
#include "game.h"

omniscia::core::CE_EntityCollectEvent::CE_EntityCollectEvent() {

}

omniscia::core::CE_EntityCollectEvent::CE_EntityCollectEvent(const CE_EntityCollectEvent&) {

}

void omniscia::core::CE_EntityCollectEvent::operator=(const CE_EntityCollectEvent&) {

}

omniscia::core::CE_EntityCollectEvent::CE_EntityCollectEvent(const CE_EntityCollectProp& data) : CE_EntityCollectProp(data), CE_Event(*(CE_Prop*)&data) {

}

void omniscia::core::CE_EntityCollectEvent::execute() {
    CutsceneDataPoolType* ptrParrentCutsceneDataPool = get_cutscene_data_pool();
    if(ptrParrentCutsceneDataPool == nullptr) 
        return;
    
    auto scene = Game::get_instance().get_active_scene();

    if(scene == nullptr) 
        return;
    
    CutsceneDataPoolType& _dataPool = *ptrParrentCutsceneDataPool;
    UUID* entityUUID = (UUID*)_dataPool[_entityTmpName].get();

    std::shared_ptr<Entity> entityPtr= scene->find_static_entity_by_uuid(*entityUUID);
    if(entityPtr == nullptr) return;

    ECS_Index<ECS_PlayerCollectorController> collectionIndex = entityPtr->index<ECS_PlayerCollectorController>();
    
    if(!collectionIndex.is_success()) 
        return;

    ECS_PlayerCollectorController& comp = entityPtr->ref_unsafe(collectionIndex);

    comp.collect();
}
