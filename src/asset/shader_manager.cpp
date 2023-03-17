#include "shader_manager.h"

omniscia::core::ShaderAsset* omniscia::core::ShaderManager::get(const std::string& key) {
    return &_data[key];
}

void omniscia::core::ShaderManager::add_asset(const std::string& file_path, const std::string& key, const ShaderAssetType& shaderType) {
    _data.insert({key, ShaderAsset(file_path, shaderType)});
}

void omniscia::core::ShaderManager::load_assets() {
    for(std::pair<const std::string, omniscia::core::ShaderAsset> &asset : _data) {

        //TODO Check errors
        asset.second.load_asset();
    }
}
