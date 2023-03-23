#ifndef _ANIMATION_ASSET_H_
#define _ANIMATION_ASSET_H_

#include "animation.h"
#include "types.tpp"
#include "asset.tpp"

namespace omniscia::core {
    class AnimationAsset : public Asset<Animation> {
        static u32 _count;

        public:
            AnimationAsset();
            AnimationAsset(const Animation& animation);

            static u32 get_count();
    };
}

#endif