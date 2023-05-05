/**
 * @file 
 * sound_engine.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _SOUND_ENGINE_H_
#define _SOUND_ENGINE_H_

#include <iostream>

#include "sound_pool.h"
#include "types.tpp"

namespace omniscia::core {
    using namespace omni::types;
    
    /**
     * @brief SoundEngine - class used for managing 
     * sound pool and miniaudio sound engine
    */
    class SoundEngine {
        private:
            /** @brief Instance of the miniaudio engine */
            ma_engine _engine;

            /** @brief Instance of the sound pool */
            SoundPool<64> _soundPool;

        public:
            /**
             * @brief Initializes sound engine
             * 
             * @return returns -1 if not success
            */
            void initialize();

            /** @brief Unutilizes sound engine */
            void unutilize();

            /**
             * @brief Returns reference to the miniaudio audio engine instance
             * 
             * @return reference to the miniaudio audio instance
            */
            ma_engine& get_backend();
            
            /**
             * @brief Returns reference to the active sound pool
             * 
             * @return reference to the sound pool 
            */
            SoundPool<64>& ref_sound_pool();
            
            /**
             * @brief Get the singleton instance of the SoundEngine
             * 
             * @return Reference to singleton instance of the SoundEngine
            */
            static SoundEngine& get_instance();
    };
}

#endif
