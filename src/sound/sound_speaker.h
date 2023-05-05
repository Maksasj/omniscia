/**
 * @file 
 * sound_speaker.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _SOUND_SPEAKER_H_
#define _SOUND_SPEAKER_H_

#include <iostream>
#include <memory>

#include "sound_engine.h"
#include "sound_manager.h"

#include "types.tpp"

namespace omniscia::core {
    using namespace omni::types;
    
    /**
     * @brief SoundSpeaker - class used to play sound, used
     * by Sound emitter component
    */
    class SoundSpeaker {
        private:
            /** @brief Position of the sound speaker */
            Vec2f _soundSourcePos;

            /**
             * @brief Active sound slot index, if there 
             * is no sound this value is set to -1
            */
            i32 _activeSound;

        public:
            /**
             * @brief Construct a new SoundSpeaker instance and sets it to specific position 
             * 
             * @param soundSourcePos position of the new SoundSpeaker instance
            */
            SoundSpeaker(Vec2f soundSourcePos = Vec2f{0.0f, 0.0f});

            /**
             * @brief Construct a new SoundSpeaker instance and sets it to specific position 
             * 
             * @param x coordinate to be set to the new SoundSpeaker instance
             * @param y coordinate to be set to the new SoundSpeaker instance
            */
            SoundSpeaker(f32 x, f32 y);

            /**
             * @brief Invokes sound pool to play sound, by it id
             * 
             * @param _soundId sound id, that need to be played
            */
            void play(const std::string& _soundId);

            /**
             * @brief Stops plays active sound
            */
            void stop();

            /**
             * @brief Method used for updating some sound data, for exapme position
            */
            void update();

            /**
             * @brief Sets position of the sound speaker
             * 
             * @param newPos position to be set to the sound speaker 
            */
            void set_pos(const Vec2f& newPos) ;

            /**
             * @brief Sets position of the sound speaker
             * 
             * @param x coordinate to be set sound speaker
             * @param y coordinate to be set sound speaker
            */
            void set_pos(const f32& x, const f32& y);
    };
}

#endif
