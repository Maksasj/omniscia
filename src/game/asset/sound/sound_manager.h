/**
 * @file 
 * sound_manager.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _SOUND_MANAGER_H_
#define _SOUND_MANAGER_H_

#include <iostream>

#include "sound_asset.h"
#include "manager.h"

#include "sound_fx.h"

namespace omniscia::core {
    using namespace omni::types;

    /**
     * @brief 
     * SoundManager - class used for storing SoundAsset 
     * instances, manage their life time, and provides convenient 
     * way to access them at run time by any other system.
    */

    class SoundManager : Manager<SoundAsset> {
        protected:
            /** @brief Hidden default constructor */
            SoundManager() {};

            /** @brief Hidden default copy constructor */
            SoundManager(SoundManager const&) {};

            /** @brief Hidden default assignment operator */
            void operator=(SoundManager const&) {};

            /**
             * @brief _data - hash map used for storing SoundAsset object instances
            */
            std::unordered_map<std::string, SoundAsset> _data;
        
        public:
            friend class omni::reflector::FieldFriendlyScope;
            friend class omni::reflector::Reflection<SoundManager>;
            friend class omni::reflector::serialization::JsonSerializer;

            /**
             * @brief Retrieve sound asset by provided key
             * 
             * @param key of the needed SoundAsset
             * @return SoundAsset* pointer to sound asset instance 
            */
            SoundAsset* get(const std::string& key);

            /**
             * @brief Adds SoundAsset, and binds it to provided key
             * 
             * @param filePath path to the sound asset file
             * @param key key that will be used to store SoundAsset
            */
            void add_asset(const std::string& filePath, const std::string& key);
            
            void add_assets(const std::string& filePath);
            
            /** @brief Checks is all asset exist */
            void check_assets() const;

            /** @brief Loads all assets */
            void load_assets();

            /**
             * @brief Get the singleton instance of the SoundAsset
             * 
             * @return Reference to singleton instance of the SoundAsset
            */
            static SoundManager& get_instance() {
                static SoundManager instance;
                return instance;
            }
    };
};

OMNI_ADAPT_STRUCTURE_NAME(omniscia::core, SoundManager, _data);

#endif
