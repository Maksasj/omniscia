#include "animation_asset.h"

u32 omniscia::core::AnimationAsset::_count = 0;

omniscia::core::AnimationAsset::AnimationAsset() { ++_count; };

omniscia::core::AnimationAsset::AnimationAsset(const Animation& animation) {
    _asset = animation;
    ++_count;
}

u32 omniscia::core::AnimationAsset::get_count() {
    return _count;
}
