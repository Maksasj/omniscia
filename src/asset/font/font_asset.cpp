#include "font_asset.h"

omni::types::u32 omniscia::core::FontAsset::_count = 0;

omniscia::core::FontAsset::FontAsset() { ++_count; }

omniscia::core::FontAsset::FontAsset(const std::string& filePath, const FontAssetProp& prop) 
        : Asset(filePath) {
            
    _asset = prop;

    ++_count; 
}

omni::types::u32 omniscia::core::FontAsset::get_count() {
    return _count;
}
