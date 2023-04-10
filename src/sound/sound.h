#ifndef _SOUND_H_
#define _SOUND_H_

#include "sound_fx.h"
#include <iostream>
#include "types.tpp"

namespace omniscia::core {
    class Sound {
        private:
            bool is_loaded;

            ma_sound _sound;
            ma_sound_config _soundConfig;
        public:

            Sound();

            int load(const std::string& file_path);
            void unload();

            void prepare(const std::string& _soundId);
            void play();
            void stop();

            bool is_playing();

            void set_pos(const Vec3f& newPos);
            void set_pos(const f32& x, const f32& y, const f32& z);

            ma_sound& get_backend();
    };
}

#endif
