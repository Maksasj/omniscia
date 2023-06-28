#include "sound_manager.h"

omniscia::core::SoundAsset* omniscia::core::SoundManager::get(const std::string& key) {
    return &_data[key];
}

void omniscia::core::SoundManager::add_asset(const std::string& file_path, const std::string& key) {
    _data.insert({key, SoundAsset(file_path)});
}

void omniscia::core::SoundManager::add_assets(const std::string& filePath) {
    using json = nlohmann::json;

    using namespace omni::reflector;
    using namespace omni::reflector::serialization;

    std::ifstream file(filePath);
    const auto object = json::parse(file);

    SoundManager manager = JsonSerializer::json_deserialize<SoundManager>(object);

    for(const auto& asset : manager._data)
        add_asset(asset.second.get_file_path(), asset.first);

    file.close();
}

void omniscia::core::SoundManager::load_assets() {
    ma_fence fence;
    ma_fence_init(&fence);
    ma_resource_manager_pipeline_notifications notifications = ma_resource_manager_pipeline_notifications_init();
    notifications.done.pFence = &fence;

    for(std::pair<const std::string, omniscia::core::SoundAsset> &asset : _data) {
        asset.second.load_asset();
    }

    ma_fence_wait(&fence);
}

void omniscia::core::SoundManager::check_assets() const {
    for(auto& asset : _data) {
        std::string filePath = asset.second.get_file_path();
        
        if(!file_exist(filePath)) {
            throw std::runtime_error("File '" + filePath + "' do not exist");
        }
    }
}
