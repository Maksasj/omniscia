/**
 * @file 
 * sound_asset.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _SOUND_ASSET_H_
#define _SOUND_ASSET_H_

#include "asset.tpp"
#include "sound.h"

namespace omniscia::core {
    /**
     * @brief SoundAsset - class used for storing sound asset,
     * Stores file path to the sound asset
    */
    class SoundAsset : public Asset<Sound> {
        /** @brief Current count of the existing SoundAsset instances */
        static u32 _count;
        
        public:
            /** @brief Defualt construct for the SoundAsset */
            SoundAsset();
            
            /**
             * @brief Constructs new SoundAsset instance, and stores all provided information
             * 
             * @param filePath - path to the sound asset file 
            */
            SoundAsset(const std::string& filePath);

            /** @brief Loades shader */
            void load_asset();

            /**
             * @brief Get current count of existing SoundAsset instances
             * 
             * @return u32 representing the current count of SoundAsset instances
            */
            static u32 get_count();
    };
}

#endif