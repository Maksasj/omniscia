#include "animation_asset.h"

omni::types::u32 omniscia::core::AnimationAsset::_count = 0;

omniscia::core::AnimationAsset::AnimationAsset() { ++_count; };

omniscia::core::AnimationAsset::AnimationAsset(const Animation& animation) {
    _asset = animation;
    ++_count;
}

omni::types::u32 omniscia::core::AnimationAsset::get_count() {
    return _count;
}
