#include "font_manager.h"

omniscia::core::FontAsset& omniscia::core::FontManager::get(const std::string& key) {
    return _data[key];
}

void omniscia::core::FontManager::add_asset(const std::string& file_path, const std::string& key, const FontAssetProp& prop) {
    _data.insert({key, FontAsset(file_path, prop)});
    TextureManager::get_instance().add_asset(file_path, key);
}

void omniscia::core::FontManager::check_assets() const {
    for(auto& asset : _data) {
        std::string filePath = asset.second.get_file_path();
        
        if(!file_exist(filePath)) {
            throw std::runtime_error("File '" + filePath + "' do not exist");
        }
    }

    TextureManager::get_instance().check_assets();
}
