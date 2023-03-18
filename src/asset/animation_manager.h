#ifndef _ANIMATION_MANAGER_H_
#define _ANIMATION_MANAGER_H_

#include <iostream>

#include "manager.h"
#include "animation_asset.h"

namespace omniscia::core {
    class AnimationManager : Manager<AnimationAsset> {
        private:
            AnimationManager() {};
            AnimationManager(AnimationManager const&) {};
            void operator=(AnimationManager const&) {};
        protected:
            std::unordered_map<std::string, AnimationAsset> _data;
        public:
            AnimationAsset* get(const std::string& key);
            void add_asset(const AnimationAsset& animationAsset, const std::string& key);

            static AnimationManager& get_instance() {
                static AnimationManager instance;
                return instance;
            }
    };
};

#endif
