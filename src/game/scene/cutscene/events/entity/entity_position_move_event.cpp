#include "entity_position_move_event.h"
#include "game.h"

omniscia::core::CE_EntityPositionMoveEvent::CE_EntityPositionMoveEvent() {

}

omniscia::core::CE_EntityPositionMoveEvent::CE_EntityPositionMoveEvent(const CE_EntityPositionMoveEvent&) {

}

void omniscia::core::CE_EntityPositionMoveEvent::operator=(const CE_EntityPositionMoveEvent&) {

}

omniscia::core::CE_EntityPositionMoveEvent::CE_EntityPositionMoveEvent(const CE_EntityPositionMoveProp& data) : CE_EntityPositionMoveProp(data), CE_Event(*(CE_Prop*)&data) {

}

void omniscia::core::CE_EntityPositionMoveEvent::execute() {
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

    const f32 t = this->get_current_duration() / _durationTime;
    const Vec2f newPosition = _shapingFunction(_startPosition, _finishPosition, t);
    
    comp.set_pos(Vec3f{newPosition.x, newPosition.y, 0.0f});
}
