#include "sound/sound_speaker.h"

omniscia::core::SoundSpeaker::SoundSpeaker(Vec2f soundSourcePos) {
    _soundSourcePos = soundSourcePos;
    _activeSound = -1;
} 

omniscia::core::SoundSpeaker::SoundSpeaker(f32 x, f32 y) {
    _soundSourcePos = Vec2f{x, y};
    _activeSound = -1;
}

void omniscia::core::SoundSpeaker::play(const std::string& _sound_id) {
    if(_activeSound != -1) return;

    SoundPool<64>& soundPool = SoundEngine::get_instance().ref_sound_pool();

    _activeSound = soundPool.invoke_sound(_sound_id);
}

void omniscia::core::SoundSpeaker::stop() {
    if(_activeSound == -1) return;
    
    SoundPool<64>& soundPool = SoundEngine::get_instance().ref_sound_pool();

    soundPool.free_sound(_activeSound);
    _activeSound = -1;
}

void omniscia::core::SoundSpeaker::update() {
    if(_activeSound == -1) return;

    SoundPool<64>& soundPool = SoundEngine::get_instance().ref_sound_pool();

    if(soundPool.is_sound_playing(_activeSound)) {
        soundPool.position_sound(_activeSound, _soundSourcePos.x, 0.0f, _soundSourcePos.y);
    } else {
        soundPool.free_sound(_activeSound);
        _activeSound = -1;
    }
}

void omniscia::core::SoundSpeaker::set_pos(const Vec2f& newPos) {
    _soundSourcePos = newPos;
}

void omniscia::core::SoundSpeaker::set_pos(const f32& x, const f32& y) {
    _soundSourcePos.x = x;
    _soundSourcePos.y = y;
}
