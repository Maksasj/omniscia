#include "sound_loop_cutscene_event.h"
#include "game.h"

omniscia::core::CE_SoundLoopCutsceneEvent::CE_SoundLoopCutsceneEvent() {

}

omniscia::core::CE_SoundLoopCutsceneEvent::CE_SoundLoopCutsceneEvent(const CE_SoundLoopCutsceneEvent&) {

}

void omniscia::core::CE_SoundLoopCutsceneEvent::operator=(const CE_SoundLoopCutsceneEvent&) {

}

omniscia::core::CE_SoundLoopCutsceneEvent::CE_SoundLoopCutsceneEvent(const CE_SoundLoopCutsceneProp& data) : CE_SoundLoopCutsceneProp(data), CE_Event(*(CE_Prop*)&data) {

}

void omniscia::core::CE_SoundLoopCutsceneEvent::execute() {
    CutsceneDataPoolType* ptrParrentCutsceneDataPool = get_cutscene_data_pool();
    if(ptrParrentCutsceneDataPool == nullptr) 
        return;

    CutsceneDataPoolType& _dataPool = *ptrParrentCutsceneDataPool;
    SoundPool<64>& soundPool = SoundEngine::get_instance().ref_sound_pool();

    if(_dataPool.find(_soundId) == _dataPool.end()) {
        //Do not found
        const i32 _activeSound = soundPool.invoke_sound(_soundId);

        _dataPool[_soundId] = std::make_shared<i32>(_activeSound);
        return;
    }

    const i32* _currentlyActiveSound = (i32*)_dataPool[_soundId].get();

    if(_currentlyActiveSound == nullptr) {
        std::cout << "Something is wrong with sound\n";

        return;
    }

    if(!soundPool.is_sound_playing(*_currentlyActiveSound)) {
        soundPool.free_sound(*_currentlyActiveSound);

        const i32 _activeSound = soundPool.invoke_sound(_soundId);

        _dataPool[_soundId] = std::make_shared<i32>(_activeSound);
    }
}
