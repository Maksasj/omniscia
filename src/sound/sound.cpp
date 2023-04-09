#include "sound.h"

omniscia::core::Sound::Sound() {
    is_loaded = false;
}

int omniscia::core::Sound::load(const std::string& file_path) {
    // _soundConfig = ma_sound_config_init();
    // _soundConfig.pFilePath  = file_path.c_str();
    // _soundConfig.pDataSource = NULL;
    // _soundConfig.volumeSmoothTimeInPCMFrames = 400; 
    ma_result result = ma_sound_init_from_file(&omniscia::core::SoundEngine::get_instance().get_backend(), file_path.c_str(), 0, NULL, NULL, &_sound);
    //ma_result result = ma_sound_init_ex(&omniscia::core::SoundEngine::get_instance().get_backend(), &_soundConfig, &_sound);
    if (result != MA_SUCCESS) {
        return -1;
    }

    is_loaded = true;

    return 0;
}

void omniscia::core::Sound::unload() {
    if(!is_loaded) return;
    ma_sound_uninit(&_sound);
    is_loaded = false;

    // std::cout << "Unloading sound \n";
}

void omniscia::core::Sound::play() {
    if(!is_loaded) return;

    ma_sound_start(&_sound);
}

bool omniscia::core::Sound::is_playing() {
    if(!is_loaded) return false;

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
