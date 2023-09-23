#include "scene/cutscene/events/entity/entity_transparency_change_event.h"
#include "game.h"

omniscia::core::CE_EntityTransparencyChangeEvent::CE_EntityTransparencyChangeEvent() {

}

omniscia::core::CE_EntityTransparencyChangeEvent::CE_EntityTransparencyChangeEvent(const CE_EntityTransparencyChangeEvent&) {

}

void omniscia::core::CE_EntityTransparencyChangeEvent::operator=(const CE_EntityTransparencyChangeEvent&) {

}

omniscia::core::CE_EntityTransparencyChangeEvent::CE_EntityTransparencyChangeEvent(const CE_EntityTransparencyChangeProp& data) : CE_EntityTransparencyChangeProp(data), CE_Event(*(CE_Prop*)&data) {

}

void omniscia::core::CE_EntityTransparencyChangeEvent::execute() {
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

    ECS_Index<ECS_Transparency> transparencyIndex = entityPtr->index<ECS_Transparency>();
    
    if(!transparencyIndex.is_success()) 
        return;

    ECS_Transparency& comp = entityPtr->ref_unsafe(transparencyIndex);

    const f32 t = this->get_current_duration() / _durationTime;
    auto newTransparency = _shapingFunction(_startTransparency, _finishTransparency, t);
    
    comp.set_transparency(newTransparency);
}
