#ifndef _SOUND_ENGINE_H_
#define _SOUND_ENGINE_H_

#include <iostream>

#include "sound_pool.h"
#include "types.tpp"

namespace omniscia::core {
    class SoundEngine {
        private:
            ma_engine _engine;
            SoundPool<64> _soundPool;
        public:
            int initialize();
            void unutilize();

            ma_engine& get_backend();
            SoundPool<64>& ref_sound_pool();
            
            static SoundEngine& get_instance();
    };
}

#endif
