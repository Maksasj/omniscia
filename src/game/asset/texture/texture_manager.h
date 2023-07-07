/**
 * @file 
 * texture_manager.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _TEXTURE_MANAGER_H_
#define _TEXTURE_MANAGER_H_

#include <iostream>

#include "texture_asset.h"
#include "manager.h"

namespace omniscia::core {
    using namespace omni::types;

    /**
     * @brief 
     * TextureManager - class used for storing TextureAsset 
     * instances, manage their life time, and provides convenient 
     * way to access them at run time by any other system.
    */
    class TextureManager : Manager<TextureAsset> {
        protected:
            /** @brief Hidden default constructor */
            TextureManager() {};
            
            /** @brief Hidden default copy constructor */
            TextureManager(TextureManager const&) {};

            /** @brief Hidden default assignment operator */
            void operator=(TextureManager const&) {};

            /**
             * @brief _data - hash map used for storing TextureAsset object instances
            */
            std::unordered_map<std::string, TextureAsset> _data;
            
        public:
            friend class omni::reflector::FieldFriendlyScope;
            friend class omni::reflector::Reflection<TextureManager>;
            friend class omni::reflector::serialization::JsonSerializer;

            /**
             * @brief Retrieve texture asset by provided key
             * 
             * @param key of the needed TextureAsset
             * @return TextureAsset* pointer to texture asset instance 
            */
            TextureAsset& get(const std::string& key);

            /**
             * @brief Adds TextureAsset, and binds it to provided key
             * 
             * @param filePath path to the texture asset file
             * @param key key that will be used to store TextureAsset
            */
            void add_asset(const std::string& filePath, const std::string& key);
            
            void add_assets(const std::string& filePath);

            /** @brief Checks is all asset exist */
            void check_assets() const;
            
            /** @brief Loads all assets */
            void load_assets();

            /**
             * @brief Get the singleton instance of the TextureManager
             * 
             * @return Reference to singleton instance of the TextureManager
            */
            static TextureManager& get_instance() {
                static TextureManager instance;
                return instance;
            }
    };
};

OMNI_ADAPT_STRUCTURE_NAME(omniscia::core, TextureManager, _data);

#endif
