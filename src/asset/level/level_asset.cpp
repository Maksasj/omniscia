#include "level_asset.h"

omni::types::u32 omniscia::core::LevelAsset::_count = 0;

omniscia::core::LevelAsset::LevelAsset() {
    ++_count;
}

omniscia::core::LevelAsset::LevelAsset(const std::string& filePath, const LevelAssetType& levelAssetType) : Asset(filePath) {
    _asset = levelAssetType;
    ++_count;
}

void omniscia::core::LevelAsset::load_asset(Scene& scene) {
    SceneLoader::get_instance().load_scene(scene, _filePath);
}

omni::types::u32 omniscia::core::LevelAsset::get_count() {
    return _count;
}
