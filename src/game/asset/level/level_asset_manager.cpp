#include "asset/level/level_asset_manager.h"

omniscia::core::LevelAsset* omniscia::core::LevelAssetManager::get(const std::string& key) {
    return &_data[key];
}

void omniscia::core::LevelAssetManager::add_asset(const std::string& file_path, const std::string& key, const LevelAssetType& levelType) {
    _data.insert({key, LevelAsset(file_path, levelType)});
}

void omniscia::core::LevelAssetManager::check_assets() const {
    for(auto& asset : _data) {
        std::string filePath = asset.second.get_file_path();
        
        if(!file_exist(filePath)) {
            throw std::runtime_error("File '" + filePath + "' do not exist");
        }
    }
}
