#include "sound_engine.h"

void omniscia::core::SoundEngine::initialize() {
    ma_result result = ma_engine_init(NULL, &_engine);
    
    if (result != MA_SUCCESS)
        throw std::runtime_error("Failed to initialize audio engine.");
}

void omniscia::core::SoundEngine::unutilize() {
    ma_engine_uninit(&_engine);
}

omniscia::core::SoundEngine& omniscia::core::SoundEngine::get_instance() {
    static SoundEngine soundEngine;
    return soundEngine;
}

ma_engine& omniscia::core::SoundEngine::get_backend() {
    return _engine;
}

omniscia::core::SoundPool<64>& omniscia::core::SoundEngine::ref_sound_pool() {
    return _soundPool;
}
