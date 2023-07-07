#ifndef _FONT_ASSET_H_
#define _FONT_ASSET_H_

#include "asset.tpp"

namespace omniscia::core {
    using namespace omni::types;

    struct FontAssetProp {
        i8 _startCharacter;
        i8 _charactersPerRow;
        Vec2f _frameSize;
    };

    class FontAsset : public Asset<FontAssetProp> {
        private:
            static u32 _count;

        public:
            FontAsset();
            FontAsset(const std::string& filePath, const FontAssetProp& prop);

            static u32 get_count();
    };
}

#endif