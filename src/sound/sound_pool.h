/**
 * @file 
 * sound_pool.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _SOUND_POOL_H_
#define _SOUND_POOL_H_

#include <iostream>
#include <bitset>

#include "sound.h"
#include "omni_types.tpp"
#include "debug_ui.h"

namespace omniscia::core {
    using namespace omni::types;
    
    /**
     * @brief SoundPool - class used for storing all sounds, manages
     * sound play time, positioning, auto loading and unloading
     * 
     * @tparam __size - how much sounds can be played simultaneously
    */
    template<unsigned long __size>
    class SoundPool {
        private:
            /** @brief Array that stores all sound instances */
            Sound _sounds[__size];
            
            /** @brief Array that shows that sound are currently available */
            u8 _availableSounds[__size];
            
            /** @brief How much sound is currently playing */
            i8 _currentlyPlayingSoundCount;
            
            /**
             * @brief Finds first available sound slot index
             * 
             * @return index of the available sound slot | returns __size is there is not available slots
            */
            i32 find_first_available_sound_slot() {
                for(auto i = 0; i < __size; ++i)
                    if(_availableSounds[i] == true)
                        return i;

                return __size;
            }

        public:
            /** @brief Construct a new SoundPool instance */
            SoundPool() {
                for(u32 i = 0; i < __size; ++i)
                    _availableSounds[i] = true;

                _currentlyPlayingSoundCount = 0;
            }

            /**
             * @brief Invokes sound, starts play it 
             * if there is an available slot automaticlly 
             * loads a new miniaudio sound
             * 
             * @param soundId id of the sound
             * @return index of the sound slot that was used by this sound | -1 if sound have not played
            */
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
                DebugInfo::get_instance().get_metrics()._currentlyPlayingSoundCount = _currentlyPlayingSoundCount;

                return availableSoundIndex;
            }

            /**
             * @brief Stops sound by it sound slot index
             * 
             * @param soundIndex index of the sound that should be stopped
            */
            void free_sound(const i32& soundIndex) {
                if(soundIndex >= __size) return;
                if(soundIndex < 0) return;

                Sound& sound = _sounds[soundIndex];
                if(sound.is_playing())
                    sound.stop();
                
                sound.unload();
                --_currentlyPlayingSoundCount;
                DebugInfo::get_instance().get_metrics()._currentlyPlayingSoundCount = _currentlyPlayingSoundCount;

                _availableSounds[soundIndex] = true;
            }

            /**
             * @brief Check by sound slot id, if it is now playing
             * 
             * @param soundIndex index of the sound slot, that need to be checked
             * @return true - sound is playing
             * @return false - sound is not playing 
            */
            bool is_sound_playing(const i32& soundIndex) {
                if(soundIndex >= __size) return false;
                if(soundIndex < 0) return false;

                Sound& sound = _sounds[soundIndex];
                
                return sound.is_playing();
            }

            /**
             * @brief Updates sound possiotiong by sound slot index
             * 
             * @param soundIndex index of the sound slot
             * @param newPos position to be set to the sound
            */
            void position_sound(const i32& soundIndex, const Vec3f& newPos) {
                if(soundIndex >= __size) return;
                if(soundIndex < 0) return;

                Sound& sound = _sounds[soundIndex];
                sound.set_pos(newPos);
            }

            /**
             * @brief Updates sound possiotiong by sound slot index
             * 
             * @param soundIndex index of the sound slot
             * @param x coordinate to be set to the sound
             * @param y coordinate to be set to the sound
             * @param z coordinate to be set to the sound
            */
            void position_sound(const i32& soundIndex, const f32& x, const f32& y, const f32& z) {
                if(soundIndex >= __size) return;
                if(soundIndex < 0) return;

                Sound& sound = _sounds[soundIndex];
                sound.set_pos(x, y, z);
            }
    };
}

#endif
