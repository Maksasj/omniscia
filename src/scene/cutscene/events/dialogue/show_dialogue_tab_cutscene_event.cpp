#include "show_dialogue_tab_cutscene_event.h"
#include "game.h"

omniscia::core::CE_ShowDialogueTabEvent::CE_ShowDialogueTabEvent() {

}

omniscia::core::CE_ShowDialogueTabEvent::CE_ShowDialogueTabEvent(const CE_ShowDialogueTabEvent&) {

}

void omniscia::core::CE_ShowDialogueTabEvent::operator=(const CE_ShowDialogueTabEvent&) {

}

omniscia::core::CE_ShowDialogueTabEvent::CE_ShowDialogueTabEvent(const CE_ShowDialogueTabProp& data) : CE_ShowDialogueTabProp(data), CE_Event(*(CE_Prop*)&data) {

}

void omniscia::core::CE_ShowDialogueTabEvent::execute() {
    CutsceneDataPoolType* ptrParrentCutsceneDataPool = get_cutscene_data_pool();
    if(ptrParrentCutsceneDataPool == nullptr) 
        return;
    
    auto scene = Game::get_instance().get_active_scene();

    if(scene == nullptr) 
        return;

    Vec3f pos = Camera::get_instance().get_pos();
    UUID entityUUID = scene->add_static_entity<DialogueTab>(Vec2f{pos.x, pos.y + 0.3f});
    
    CutsceneDataPoolType& _dataPool = *ptrParrentCutsceneDataPool;

    scene->time_sync();
}
