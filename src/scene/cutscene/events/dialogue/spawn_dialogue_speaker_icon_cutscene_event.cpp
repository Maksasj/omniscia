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
        ._layer = 1,
        ._pos = Vec2f{pos.x, pos.y},
        ._scale = Vec2f{0.2f, 0.2f},
    });
    
    CutsceneDataPoolType& _dataPool = *ptrParrentCutsceneDataPool;
    _dataPool[_entityTmpName] = std::make_shared<UUID>(entityUUID);

    scene->time_sync();
}
