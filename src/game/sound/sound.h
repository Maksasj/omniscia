/**
 * @file 
 * sound.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _SOUND_H_
#define _SOUND_H_

#include "sound_fx.h"
#include <iostream>
#include "omni_types.tpp"

namespace omniscia::core {
    using namespace omni::types;
    
    /**
     * @brief Sound - class used for playing sounds,
     * stores miniaudio sound instances, configuration, 
     * and manages it loading and playing
    */
    class Sound {
        private:
            /**
             * @brief Boolean value that shows 
             * if sound is currently laoded
             * (can be changet during life time)
            */
            bool _isLoaded;

            /** @brief miniaudio sound instance */
            ma_sound _sound;
            
            /** @brief miniaudio soind configuration */
            ma_sound_config _soundConfig;

        public:
            /** @brief Defualt Sound constructor */
            Sound();
            
            /**
             * @brief Loads sound from given file, used only by sound manager
             * 
             * @param filePath path to the sound asset file
             * @return returns 0 if success 
            */
            int load(const std::string& filePath);
            
            /**
             * @brief Unloads miniaudio sound from 
             * the memory and sets _isLoaded to false
            */
            void unload();

            /**
             * @brief Creates new miniaudio sound instance
             * by sound id
             * 
             * @param _soundId sound id 
            */
            void prepare(const std::string& _soundId);
            
            /**
             * @brief Plays sound if it is loaded
            */
            void play();

            /**
             * @brief Stops playing sound 
            */
            void stop();

            /**
             * @brief Checks if sound is currently playing
             * 
             * @return true - sound instance is currently playing
             * @return false - sound instance is not currently playing
            */
            bool is_playing();

            /**
             * @brief Set the possition of the miniaudio sound
             * 
             * @param newPos possition to be set to miniadio sound
            */
            void set_pos(const Vec3f& newPos);
            
            /**
             * @brief Set the possition of the miniaudio sound
             * 
             * @param x coordinate to be set to miniadio sound
             * @param y coordinate to be set to miniadio sound
            */
            void set_pos(const f32& x, const f32& y, const f32& z);

            /**
             * @brief Returns miniaudio sound instance in the current Sound intance
             * 
             * @return reference to the miniaudio sound instance
            */
            ma_sound& get_backend();
    };
}

#endif
