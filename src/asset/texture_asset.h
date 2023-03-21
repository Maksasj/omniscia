#ifndef _TEXTURE_ASSET_H_
#define _TEXTURE_ASSET_H_

#include "asset.tpp"

#include "texture.h"

namespace omniscia::core {
    using namespace omniscia::gfx::texture;

    class TextureAsset : public Asset<Texture> {
        public:
            TextureAsset();
            TextureAsset(const std::string& file_path);

            void load_asset();
    };
}

#endif