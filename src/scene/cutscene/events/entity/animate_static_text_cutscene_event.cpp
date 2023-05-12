#include "animate_static_text_cutscene_event.h"
#include "game.h"

omniscia::core::CE_AnimateStaticTextEvent::CE_AnimateStaticTextEvent() {

}

omniscia::core::CE_AnimateStaticTextEvent::CE_AnimateStaticTextEvent(const CE_AnimateStaticTextEvent&) {

}

void omniscia::core::CE_AnimateStaticTextEvent::operator=(const CE_AnimateStaticTextEvent&) {

}

omniscia::core::CE_AnimateStaticTextEvent::CE_AnimateStaticTextEvent(const CE_AnimateStaticTextProp& data) : CE_AnimateStaticTextProp(data), CE_Event(*(CE_Prop*)&data) {

}

void omniscia::core::CE_AnimateStaticTextEvent::execute() {
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

    ECS_Index<ECS_TextRenderer> textRendererIndex = entityPtr->index<ECS_TextRenderer>();
    
    if(!textRendererIndex.is_success()) 
        return;

    ECS_TextRenderer& comp = entityPtr->ref_unsafe(textRendererIndex);

    const f32 t = this->get_current_duration() / _durationTime;
    
    auto newCharacterCount = _shapingFunction(_startingCharacterCount, _finishCharacterCount, t);

    comp.set_text_to_render(_text.substr(0, round(newCharacterCount)), 0.31f, 0.8f, 24u);    
}
