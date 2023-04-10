#ifndef _SOUND_POOL_H_
#define _SOUND_POOL_H_

#include <iostream>
#include <bitset>

#include "sound.h"
#include "types.tpp"
#include "debug_ui.h"

namespace omniscia::core {
    template<unsigned long __size>
    class SoundPool {
        private:
            Sound _sounds[__size];
            u8 _availableSounds[__size];
            i8 _currentlyPlayingSoundCount;
            
            i32 find_first_available_sound_slot() {
                for(auto i = 0; i < __size; ++i)
                    if(_availableSounds[i] == true)
                        return i;

                return __size;
            }
        public:
            SoundPool() {
                for(u32 i = 0; i < __size; ++i)
                    _availableSounds[i] = true;

                _currentlyPlayingSoundCount = 0;
            }


            i32 invoke_sound(const std::string& soundId) {
                i32 availableSoundIndex = find_first_available_sound_slot();

                if(availableSoundIndex >= __size) 
                    return -1;
                
                Sound& sound = _sounds[availableSoundIndex];
                if(sound.is_playing()) return -1;
                
                sound.prepare(soundId);
                sound.play();

                _availableSounds[availableSoundIndex] = false;
                ++_currentlyPlayingSoundCount;
                DebugUI::get_instance().get_metrics()._currentlyPlayingSoundCount = _currentlyPlayingSoundCount;

                return availableSoundIndex;
            }

            void free_sound(const i32& soundIndex) {
                if(soundIndex >= __size) return;
                if(soundIndex < 0) return;

                Sound& sound = _sounds[soundIndex];
                if(sound.is_playing())
                    sound.stop();
                
                sound.unload();
                --_currentlyPlayingSoundCount;
                DebugUI::get_instance().get_metrics()._currentlyPlayingSoundCount = _currentlyPlayingSoundCount;

                _availableSounds[soundIndex] = true;
            }

            bool is_sound_playing(const i32& soundIndex) {
                if(soundIndex >= __size) return false;
                if(soundIndex < 0) return false;

                Sound& sound = _sounds[soundIndex];
                
                return sound.is_playing();
            }

            void position_sound(const i32& soundIndex, const Vec3f& newPos) {
                if(soundIndex >= __size) return false;
                if(soundIndex < 0) return false;

                Sound& sound = _sounds[soundIndex];
                sound.set_pos(newPos);
            }

            void position_sound(const i32& soundIndex, const f32& x, const f32& y, const f32& z) {
                if(soundIndex >= __size) return;
                if(soundIndex < 0) return;

                Sound& sound = _sounds[soundIndex];
                sound.set_pos(x, y, z);
            }
    };
}

#endif
