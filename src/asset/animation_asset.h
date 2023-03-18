#ifndef _ANIMATION_ASSET_H_
#define _ANIMATION_ASSET_H_

#include "asset.tpp"
#include "animation.h"

namespace omniscia::core {
    class AnimationAsset : public Asset<Animation> {
        public:
            AnimationAsset() {};
            
            AnimationAsset(const Animation& animation) {
                _asset = animation;
            }
    };
}

#endif