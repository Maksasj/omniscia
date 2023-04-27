#include "texture_manager.h"

omniscia::core::TextureAsset& omniscia::core::TextureManager::get(const std::string& key) {
    return _data[key];
}

void omniscia::core::TextureManager::add_asset(const std::string& file_path, const std::string& key) {
    _data.insert({key, TextureAsset(file_path)});
}

void omniscia::core::TextureManager::load_assets() {
    for(std::pair<const std::string, omniscia::core::TextureAsset> &asset : _data) {

        //TODO Check errors
        asset.second.load_asset();
    }
}

void omniscia::core::TextureManager::check_assets() const {
    for(auto& asset : _data) {
        std::string filePath = asset.second.get_file_path();
        
        if(!file_exist(filePath)) {
            throw std::runtime_error("File '" + filePath + "' do not exist");
        }
    }
}
