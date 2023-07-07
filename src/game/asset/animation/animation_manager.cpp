#include "animation_manager.h"

omniscia::core::AnimationAsset* omniscia::core::AnimationManager::get(const std::string& key) {
    return &_data[key];
}

void omniscia::core::AnimationManager::add_asset(const AnimationAsset& animationAsset, const std::string& key) {
    _data.insert({key, animationAsset});
}
