#include "entity_position_set_event.h"
#include "game.h"

omniscia::core::CE_EntityPositionSetEvent::CE_EntityPositionSetEvent() {

}

omniscia::core::CE_EntityPositionSetEvent::CE_EntityPositionSetEvent(const CE_EntityPositionSetEvent&) {

}

void omniscia::core::CE_EntityPositionSetEvent::operator=(const CE_EntityPositionSetEvent&) {

}

omniscia::core::CE_EntityPositionSetEvent::CE_EntityPositionSetEvent(const CE_EntityPositionSetProp& data) : CE_EntityPositionSetProp(data), CE_Event(*(CE_Prop*)&data) {

}

void omniscia::core::CE_EntityPositionSetEvent::execute() {
    CutsceneDataPoolType* ptrParrentCutsceneDataPool = get_cutscene_data_pool();
    if(ptrParrentCutsceneDataPool == nullptr) 
        return;
    
    auto scene = Game::get_instance().get_active_scene();

    if(scene == nullptr) 
        return;
    
    CutsceneDataPoolType& _dataPool = *ptrParrentCutsceneDataPool;
    UUID* entityUUID = (UUID*)_dataPool[_entityTmpName].get();

    std::shared_ptr<Entity> entityPtr= scene->get_static_entity_by_uuid(*entityUUID);
    if(entityPtr == nullptr) return;

    ECS_Index<ECS_Positioned> positionIndex = entityPtr->index<ECS_Positioned>();
    
    if(!positionIndex.is_success()) 
        return;

    ECS_Positioned& comp = entityPtr->ref_unsafe(positionIndex);

    comp.set_pos(Vec3f{_newPosition});
}
