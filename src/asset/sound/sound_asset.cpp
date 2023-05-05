#include "sound_asset.h"

omni::types::u32 omniscia::core::SoundAsset::_count = 0;

omniscia::core::SoundAsset::SoundAsset() {
    ++_count;
}

omniscia::core::SoundAsset::SoundAsset(const std::string& filePath) : Asset(filePath) {
    ++_count;
}

void omniscia::core::SoundAsset::load_asset() {
    _asset.load(_filePath);
}

omni::types::u32 omniscia::core::SoundAsset::get_count() {
    return _count;
}
