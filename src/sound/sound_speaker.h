#ifndef _SOUND_SPEAKER_H_
#define _SOUND_SPEAKER_H_

#include <iostream>
#include <memory>

#include "sound_engine.h"
#include "sound_manager.h"

#include "types.tpp"

namespace omniscia::core {
    class SoundSpeaker {
        Vec2f _soundSourcePos;

        Sound* _soundInstance;
        public:
            SoundSpeaker(Vec2f soundSourcePos = Vec2f{0.0f, 0.0f});
            SoundSpeaker(f32 x, f32 y);

            void play(const std::string& _sound_id);
            void stop();

            void update();

            void set_pos(const Vec2f& newPos) ;
            void set_pos(const f32& x, const f32& y);
    };
}

#endif
