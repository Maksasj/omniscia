#ifndef _TEXTURE_ASSET_H_
#define _TEXTURE_ASSET_H_

#include "asset.tpp"
#include "texture.h"

namespace omniscia::core {
    using namespace omniscia::gfx::texture;

    class TextureAsset : public Asset<Texture> {
        static u32 _count;

        public:
            TextureAsset();
            TextureAsset(const std::string& file_path);

            void load_asset();

            static u32 get_count();
    };
}

#endif