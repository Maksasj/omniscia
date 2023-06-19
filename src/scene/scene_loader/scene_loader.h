/**
 * @file 
 * scene_loader.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _SCENE_LOADER_H_
#define _SCENE_LOADER_H_

#include "omni_serializer.h"

#include "omni_types.tpp"
#include "scene.h"

namespace omniscia::core {
    using namespace omni::types;
    
    /**
     * @brief SceneLoader - class used for loading 
     * level binary data as an active scene
    */
    class SceneLoader {
        public:
            /**
             * @brief Method that loads scene binary data from file, to
             * existing scene instance(clearing scene before)
             * 
             * @param level reference to existing scene instance
            */
            void load_scene(Scene& level, const std::string& path);

            /**
             * @brief Get singleton instance of the SceneLoader class
             * 
             * @return SceneLoader& reference to the active SceneLoader single ton
            */
            static SceneLoader& get_instance();
    };
}

#endif
