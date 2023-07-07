#include "spawn_pause_text_cutscene_event.h"
#include "game.h"

omniscia::core::CE_SpawnPauseTextEvent::CE_SpawnPauseTextEvent() {

}

omniscia::core::CE_SpawnPauseTextEvent::CE_SpawnPauseTextEvent(const CE_SpawnPauseTextEvent&) {

}

void omniscia::core::CE_SpawnPauseTextEvent::operator=(const CE_SpawnPauseTextEvent&) {

}

omniscia::core::CE_SpawnPauseTextEvent::CE_SpawnPauseTextEvent(const CE_SpawnPauseTextProp& data) : CE_SpawnPauseTextProp(data), CE_Event(*(CE_Prop*)&data) {

}

void omniscia::core::CE_SpawnPauseTextEvent::execute() {
    CutsceneDataPoolType* ptrParrentCutsceneDataPool = get_cutscene_data_pool();
    if(ptrParrentCutsceneDataPool == nullptr) 
        return;
    
    auto scene = Game::get_instance().get_active_scene();

    if(scene == nullptr) 
        return;

    UUID entityUUID = scene->add_static_entity<Image>((ImageProp) {
        ._texture = "pause_text",
        ._pos = Vec2f{0.0f, 0.6f},
        ._scale = Vec2f{0.2f, 0.2f},
    });
    
    CutsceneDataPoolType& _dataPool = *ptrParrentCutsceneDataPool;
    _dataPool[_entityTmpName] = std::make_shared<UUID>(entityUUID);

    scene->time_sync();
}
