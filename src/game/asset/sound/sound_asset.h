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
    using namespace omni::types;

    /**
     * @brief SoundAsset - class used for storing sound asset,
     * Stores file path to the sound asset
    */
    class SoundAsset : public Asset<Sound> {
        /** @brief Current count of the existing SoundAsset instances */
        static u32 _count;
        
        public:
            friend class omni::reflector::FieldFriendlyScope;
            friend class omni::reflector::Reflection<SoundAsset>;
            friend class omni::reflector::serialization::JsonSerializer;

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

OMNI_ADAPT_STRUCTURE_NAME(omniscia::core, SoundAsset, _filePath);

#endif