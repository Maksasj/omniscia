/**
 * @file 
 * texture_asset.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _TEXTURE_ASSET_H_
#define _TEXTURE_ASSET_H_

#include "asset.tpp"
#include "texture.h"

namespace omniscia::core {
    using namespace omni::types;
    using namespace omniscia::gfx::texture;

    /**
     * @brief TextureAsset - class used for storing texture asset,
     * Stores file path to the texture asset, as well as texture type
    */
    class TextureAsset : public Asset<Texture> {
        private:
            /** @brief Current count of the existing TextureAsset instances */
            static u32 _count;

        public:
            friend class omni::reflector::FieldFriendlyScope;
            friend class omni::reflector::Reflection<TextureAsset>;
            friend class omni::reflector::serialization::JsonSerializer;
            
            /** @brief Defualt construct for the TextureAsset */
            TextureAsset();
            
            /**
             * @brief Constructs new TextureAsset instance, and stores all provided information
             * 
             * @param filePath - path to the texture asset file 
            */
            TextureAsset(const std::string& filePath);

            /** @brief Loades shader */
            void load_asset();

            /**
             * @brief Get current count of existing TextureAsset instances
             * 
             * @return u32 representing the current count of TextureAsset instances
            */
            static u32 get_count();
    };
}

OMNI_ADAPT_STRUCTURE_NAME(omniscia::core, TextureAsset, _filePath);

#endif