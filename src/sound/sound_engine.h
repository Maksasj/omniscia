#ifndef _SOUND_ENGINE_H_
#define _SOUND_ENGINE_H_

#include <iostream>

#include "sound_fx.h"
#include "types.tpp"

namespace omniscia::core {
    class SoundEngine {
        private:
            ma_engine engine;
        public:
            int initialize();
            void unutilize();

            ma_engine& get_backend();

            static SoundEngine& get_instance();
    };
}

#endif
