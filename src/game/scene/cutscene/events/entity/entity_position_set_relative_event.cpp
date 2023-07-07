#include "entity_position_set_relative_event.h"
#include "game.h"

omniscia::core::CE_EntityPositionSetRelativeEvent::CE_EntityPositionSetRelativeEvent() {

}

omniscia::core::CE_EntityPositionSetRelativeEvent::CE_EntityPositionSetRelativeEvent(const CE_EntityPositionSetRelativeEvent&) {

}

void omniscia::core::CE_EntityPositionSetRelativeEvent::operator=(const CE_EntityPositionSetRelativeEvent&) {

}

omniscia::core::CE_EntityPositionSetRelativeEvent::CE_EntityPositionSetRelativeEvent(const CE_EntityPositionSetRelativeProp& data) : CE_EntityPositionSetRelativeProp(data), CE_Event(*(CE_Prop*)&data) {

}

void omniscia::core::CE_EntityPositionSetRelativeEvent::execute() {
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

    ECS_Index<ECS_Positioned> positionIndex = entityPtr->index<ECS_Positioned>();
    
    if(!positionIndex.is_success()) 
        return;

    ECS_Positioned& comp = entityPtr->ref_unsafe(positionIndex);
    Vec3f& currentPos = comp.ref_pos();

    Vec3f pos = Camera::get_instance().get_pos();
    currentPos.x = pos.x + _relativePosition.x;
    currentPos.y = pos.y + _relativePosition.y;
}
