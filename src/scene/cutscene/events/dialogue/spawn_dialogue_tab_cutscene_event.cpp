#include "spawn_dialogue_tab_cutscene_event.h"
#include "game.h"

omniscia::core::CE_SpawnDialogueTabEvent::CE_SpawnDialogueTabEvent() {

}

omniscia::core::CE_SpawnDialogueTabEvent::CE_SpawnDialogueTabEvent(const CE_SpawnDialogueTabEvent&) {

}

void omniscia::core::CE_SpawnDialogueTabEvent::operator=(const CE_SpawnDialogueTabEvent&) {

}

omniscia::core::CE_SpawnDialogueTabEvent::CE_SpawnDialogueTabEvent(const CE_SpawnDialogueTabProp& data) : CE_SpawnDialogueTabProp(data), CE_Event(*(CE_Prop*)&data) {

}

void omniscia::core::CE_SpawnDialogueTabEvent::execute() {
    CutsceneDataPoolType* ptrParrentCutsceneDataPool = get_cutscene_data_pool();
    if(ptrParrentCutsceneDataPool == nullptr) 
        return;
    
    auto scene = Game::get_instance().get_active_scene();

    if(scene == nullptr) 
        return;

    Vec3f pos = Camera::get_instance().get_pos();
    UUID entityUUID = scene->add_static_entity<DialogueTab>(Vec2f{pos.x, pos.y});
    
    CutsceneDataPoolType& _dataPool = *ptrParrentCutsceneDataPool;
    _dataPool[_entityTmpName] = std::make_shared<UUID>(entityUUID);

    scene->time_sync();
}
