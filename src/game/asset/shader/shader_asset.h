/**
 * @file 
 * shader_asset.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _SHADER_ASSET_H_
#define _SHADER_ASSET_H_

#include "asset/shader/shader_asset_type.h"
#include "asset/asset.tpp"

namespace omniscia::core {
    using namespace omni::types;

    /**
     * @brief ShaderAsset - class used for storing shader asset,
     * Stores file path to the shader asset, as well as shader type
    */
    class ShaderAsset : public Asset<ShaderAssetType> {
        private:
            /** @brief Current count of the existing ShaderAsset instances */
            static u32 _count;
        
        public:
            /** @brief Defualt construct for the ShaderAsset */
            ShaderAsset();
            
            /**
             * @brief Constructs new ShaderAsset instance, and stores all provided information
             * 
             * @param filePath - path to the shader asset file 
             * @param shaderType - type of the shader asset (vertex or frament)
            */
            ShaderAsset(const std::string& filePath, const ShaderAssetType& shaderType);

            /** @brief Loades shader */
            void load_asset();

            /**
             * @brief Get current count of existing ShaderAsset instances
             * 
             * @return u32 representing the current count of ShaderAsset instances
            */
            static u32 get_count();
    };
}

#endif