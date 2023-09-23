/**
 * @file 
 * shader_manager.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _SHADER_MANAGER_H_
#define _SHADER_MANAGER_H_

#include <iostream>

#include "asset/shader/shader_asset.h"
#include "asset/manager.h"

namespace omniscia::core {
    using namespace omni::types;

    /**
     * @brief 
     * ShaderManager - class used for storing ShaderAsset 
     * instances, manage their life time, and provides convenient 
     * way to access them at run time by any other system.
    */
    class ShaderManager : Manager<ShaderAsset> {
        private:
            /** @brief Hidden default constructor */
            ShaderManager() {};
            
            /** @brief Hidden default copy constructor */
            ShaderManager(ShaderManager const&) {};

            /** @brief Hidden default assignment operator */
            void operator=(ShaderManager const&) {};

        protected:
            /**
             * @brief _data - hash map used for storing ShaderAsset object instances
            */
            std::unordered_map<std::string, ShaderAsset> _data;
        
        public:
            /**
             * @brief Retrieve shader asset by provided key
             * 
             * @param key of the needed ShaderAsset
             * @return ShaderAsset* pointer to shader asset instance 
            */
            ShaderAsset* get(const std::string& key);

            /**
             * @brief Adds ShaderAsset, and binds it to provided key
             * 
             * @param filePath path to the shader asset file
             * @param key key that will be used to store ShaderAsset
             * @param shaderType type of the shader
            */
            void add_asset(const std::string& filePath, const std::string& key, const ShaderAssetType& shaderType);
            
            /** @brief Checks is all asset exist */
            void check_assets() const;

            /** @brief Loads all assets */
            void load_assets();
            
            /**
             * @brief Get the singleton instance of the ShaderManager
             * 
             * @return Reference to singleton instance of the ShaderManager
            */
            static ShaderManager& get_instance() {
                static ShaderManager instance;
                return instance;
            }
    };
};

#endif
