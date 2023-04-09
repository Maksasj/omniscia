#include "sound_speaker.h"

omniscia::core::SoundSpeaker::SoundSpeaker(Vec2f soundSourcePos) {
    _soundSourcePos = soundSourcePos;

    _soundInstance = new Sound();
} 

omniscia::core::SoundSpeaker::SoundSpeaker(f32 x, f32 y) {
    _soundSourcePos = Vec2f{x, y};

    _soundInstance = new Sound();
}

void omniscia::core::SoundSpeaker::play(const std::string& _sound_id) {
    if(_soundInstance->is_playing()) return;

    ma_sound& sound_backend = _soundInstance->get_backend(); 
    SoundEngine& soundEngine = SoundEngine::get_instance();
    SoundAsset* soundAsset =  SoundManager::get_instance().get(_sound_id);

    if(_soundInstance->is_loaded) {
        _soundInstance->unload();
    }

    ma_sound_init_copy(&soundEngine.get_backend(), &soundAsset->get_asset()->get_backend(), 0, NULL, &sound_backend);

    _soundInstance->is_loaded = true;
    _soundInstance->play();
}

void omniscia::core::SoundSpeaker::stop() {
    if(!_soundInstance->is_playing()) return;
    _soundInstance->stop();
    _soundInstance->unload();
}

void omniscia::core::SoundSpeaker::update() {
    /* Check is sound is currently playing */
    if(_soundInstance->is_playing()) {
        _soundInstance->set_pos(_soundSourcePos.x, 0.0f, _soundSourcePos.y);
    } else {
        _soundInstance->unload();
    }
}

void omniscia::core::SoundSpeaker::set_pos(const Vec2f& newPos) {
    _soundSourcePos = newPos;
}

void omniscia::core::SoundSpeaker::set_pos(const f32& x, const f32& y) {
    _soundSourcePos.x = x;
    _soundSourcePos.y = y;
}
