#include "spawn_dialogue_text_cutscene_event.h"
#include "game.h"

omniscia::core::CE_SpawnDialogueTextEvent::CE_SpawnDialogueTextEvent() {

}

omniscia::core::CE_SpawnDialogueTextEvent::CE_SpawnDialogueTextEvent(const CE_SpawnDialogueTextEvent&) {

}

void omniscia::core::CE_SpawnDialogueTextEvent::operator=(const CE_SpawnDialogueTextEvent&) {

}

omniscia::core::CE_SpawnDialogueTextEvent::CE_SpawnDialogueTextEvent(const CE_SpawnDialogueTextProp& data) : CE_SpawnDialogueTextProp(data), CE_Event(*(CE_Prop*)&data) {

}

void omniscia::core::CE_SpawnDialogueTextEvent::execute() {
    CutsceneDataPoolType* ptrParrentCutsceneDataPool = get_cutscene_data_pool();
    if(ptrParrentCutsceneDataPool == nullptr) 
        return;
    
    auto scene = Game::get_instance().get_active_scene();

    if(scene == nullptr) 
        return;

    Vec3f pos = Camera::get_instance().get_pos();
    UUID entityUUID = scene->add_static_entity<StaticText>(Vec2f{pos.x, pos.y + 0.3f}, Vec2f{0.035f, 0.035f}, (StaticTextProp) {
        ._fontId = "monogram-white",
        ._textToRender = "",
        ._lineLetterSpacing = 0.42f,
        ._rowLineSpacing = 0.8f,
        ._charactersPerRow = 24u,
    });

    CutsceneDataPoolType& _dataPool = *ptrParrentCutsceneDataPool;
    _dataPool[_entityTmpName] = std::make_shared<UUID>(entityUUID);

    scene->time_sync();
}
