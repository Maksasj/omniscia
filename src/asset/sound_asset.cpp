#include "sound_asset.h"

u32 omniscia::core::SoundAsset::_count = 0;

omniscia::core::SoundAsset::SoundAsset() {
    ++_count;
}

omniscia::core::SoundAsset::SoundAsset(const std::string& file_path) : Asset(file_path) {
    ++_count;
}

void omniscia::core::SoundAsset::load_asset() {
    _asset.load(_file_path);
}

u32 omniscia::core::SoundAsset::get_count() {
    return _count;
}
