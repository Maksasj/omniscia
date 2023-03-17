#ifndef _SPRITE_ASSET_H_
#define _SPRITE_ASSET_H_

#include "asset.tpp"

#include "texture.h"

namespace omniscia::core {
    using namespace omniscia::renderer::texture;

    class SpriteAsset : public Asset<Texture> {
        u32 _width;
        u32 _height;
        u32 _spriteWidth;
        u32 _spriteHeight;

        public:
            SpriteAsset();
            SpriteAsset(const std::string& file_path, u32 width, u32 height, u32 spriteWidth, u32 spriteHeight);

            void load_asset();
    };
}

#endif