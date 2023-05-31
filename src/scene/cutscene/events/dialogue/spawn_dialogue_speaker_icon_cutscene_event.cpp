#include "spawn_dialogue_speaker_icon_cutscene_event.h"
#include "game.h"

omniscia::core::CE_SpawnDialogueSpeakerIconEvent::CE_SpawnDialogueSpeakerIconEvent() {

}

omniscia::core::CE_SpawnDialogueSpeakerIconEvent::CE_SpawnDialogueSpeakerIconEvent(const CE_SpawnDialogueSpeakerIconEvent&) {

}

void omniscia::core::CE_SpawnDialogueSpeakerIconEvent::operator=(const CE_SpawnDialogueSpeakerIconEvent&) {

}

omniscia::core::CE_SpawnDialogueSpeakerIconEvent::CE_SpawnDialogueSpeakerIconEvent(const CE_SpawnDialogueSpeakerIconProp& data) : CE_SpawnDialogueSpeakerIconProp(data), CE_Event(*(CE_Prop*)&data) {

}

void omniscia::core::CE_SpawnDialogueSpeakerIconEvent::execute() {
    CutsceneDataPoolType* ptrParrentCutsceneDataPool = get_cutscene_data_pool();
    if(ptrParrentCutsceneDataPool == nullptr) 
        return;
    
    auto scene = Game::get_instance().get_active_scene();

    if(scene == nullptr) 
        return;

    Vec3f pos = Camera::get_instance().get_pos();
    UUID entityUUID = scene->add_static_entity<Image>((ImageProp) {
        ._texture = _speakerIconTextureId,
        ._transparency = 0.0f,
        ._pos = Vec2f{0.0f, 0.45f},
        ._scale = Vec2f{0.3f, 0.3f},
    });
    
    CutsceneDataPoolType& _dataPool = *ptrParrentCutsceneDataPool;
    _dataPool[_entityTmpName] = std::make_shared<UUID>(entityUUID);

    scene->time_sync();
}
