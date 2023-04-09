#include "sound_engine.h"

int omniscia::core::SoundEngine::initialize() {
    ma_result result = ma_engine_init(NULL, &engine);
    
    if (result != MA_SUCCESS) {
        std::cout << "Failed to initialize audio engine.";
        return -1;
    }

    return 0;
}

void omniscia::core::SoundEngine::unutilize() {
    ma_engine_uninit(&engine);
}

omniscia::core::SoundEngine& omniscia::core::SoundEngine::get_instance() {
    static SoundEngine soundEngine;
    return soundEngine;
}

ma_engine& omniscia::core::SoundEngine::get_backend() {
    return engine;
}

