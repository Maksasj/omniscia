/**
 * @file 
 * animation_manager.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _ANIMATION_MANAGER_H_
#define _ANIMATION_MANAGER_H_

#include <iostream>

#include "animation_asset.h"
#include "manager.h"

namespace omniscia::core {
    using namespace omni::types;

    /**
     * @brief 
     * AnimationManager - class used for storing AnimationAsset 
     * instances, manage their life time, and provides convenient 
     * way to access them at run time by any other system.
    */
    class AnimationManager : Manager<AnimationAsset> {
        private:
            /** @brief Hidden default constructor */
            AnimationManager() {};
            
            /** @brief Hidden default copy constructor */
            AnimationManager(AnimationManager const&) {};
            
            /** @brief Hidden default assignment operator */
            void operator=(AnimationManager const&) {};

        protected:
            /**
             * @brief _data - hash map used for storing AnimationAsset object instances
            */
            std::unordered_map<std::string, AnimationAsset> _data;
        public:
            /**
             * @brief Retrieve animation asset by provided key
             * 
             * @param key of the needed AnimationAsset
             * @return AnimationAsset* pointer to animation asset instance 
            */
            AnimationAsset* get(const std::string& key);
            
            /**
             * @brief Loads AnimatioAsset, and binds it to provided key
             * 
             * @param animationAsset Instance of existing AnimationAsset to be need loaded
             * @param key key that will be used to store AnimationAsset
            */
            void add_asset(const AnimationAsset& animationAsset, const std::string& key);

            /**
             * @brief Get the singleton instance of the AnimationManager
             * 
             * @return Reference to singleton instance of the AnimationManager
            */
            static AnimationManager& get_instance() {
                static AnimationManager instance;
                return instance;
            }
    };
};

#endif
