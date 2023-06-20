#include "sound.h"
#include "sound_engine.h"
#include "sound_manager.h"

omniscia::core::Sound::Sound() {
    _isLoaded = false;
}

int omniscia::core::Sound::load(const std::string& filePath) {
    _soundConfig = ma_sound_config_init();
    _soundConfig.pFilePath  = filePath.c_str();
    _soundConfig.pDataSource = NULL;
    // _soundConfig.volumeSmoothTimeInPCMFrames = 400; 

    ma_result result = ma_sound_init_from_file(&omniscia::core::SoundEngine::get_instance().get_backend(), filePath.c_str(), 0, NULL, NULL, &_sound);

    if (result != MA_SUCCESS) {
        return -1;
    }

    _isLoaded = true;

    return 0;
}

void omniscia::core::Sound::unload() {
    if(!_isLoaded) return;
    ma_sound_uninit(&_sound);
    _isLoaded = false;
}

void omniscia::core::Sound::prepare(const std::string& _soundId) {
    if(is_playing()) return;

    omniscia::core::SoundEngine& soundEngine = SoundEngine::get_instance();
    omniscia::core::SoundAsset* soundAsset =  SoundManager::get_instance().get(_soundId);

    if(_isLoaded) {
        unload();
    }
    
    ma_sound_init_copy(&soundEngine.get_backend(), &soundAsset->get_asset()->get_backend(), 0, NULL, &_sound);

    _isLoaded = true;
}

void omniscia::core::Sound::play() {
    if(!_isLoaded) return;

    ma_sound_start(&_sound);
}

bool omniscia::core::Sound::is_playing() {
    if(!_isLoaded) return false;

    return ma_sound_is_playing(&_sound);
}

void omniscia::core::Sound::set_pos(const Vec3f& newPos) {
    ma_sound_set_position(&_sound, newPos.x, newPos.y, newPos.z);
}

void omniscia::core::Sound::set_pos(const f32& x, const f32& y, const f32& z) {
    ma_sound_set_position(&_sound, x, y, z);
}

void omniscia::core::Sound::stop() {
    ma_sound_stop(&_sound);
}

ma_sound& omniscia::core::Sound::get_backend() {
    return _sound;
}
