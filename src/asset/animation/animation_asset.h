/**
 * @file 
 * animation_asset.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _ANIMATION_ASSET_H_
#define _ANIMATION_ASSET_H_

#include "animation.h"
#include "types.tpp"
#include "asset.tpp"

namespace omniscia::core {
    using namespace omni::types;

    /**
     * @brief 
     * AnimationAsset - class used for storing 
     * Animation assets inside Animation manager 
     * instance. Mostly manages file path
     * to source asset, amount of existing 
     * assets of this type, as well as provides
     * access to raw asset data.
    */
    class AnimationAsset : public Asset<Animation> {
        /** Represents the current count of existing AnimationAsset instances */
        static u32 _count;

        public:
            /**
             * @brief Construct a new Animation Asset object
             * 
            */
            AnimationAsset();

            /**
             * @brief Construct a new Animation Asset object, from existing Animation object
             * Used by animation manager
             * 
             * @param animation Raw Animation to be used as Animation asset
            */
            AnimationAsset(const Animation& animation);

            /**
             * @brief Get current count of existing AnimationAsset instances
             * 
             * @return u32 representing the current count of AnimationAsset instances
            */
            static u32 get_count();
    };
}

#endif