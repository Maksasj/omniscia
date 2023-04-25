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

#include "types.tpp"
#include "scene.h"

namespace omniscia::core {
    /**
     * @brief SceneLoader - class used for loading 
     * level binary data as an active scene
    */
    class SceneLoader {
        private:
            /**
             * @brief TileData - temporary class
             * used for storing some tile data
            */
            struct TileData {
                /**
                 * @brief x position coordiante
                */
                f32 x;

                /**
                 * @brief y position coordiante
                */
                f32 y;

                /**
                 * @brief tile width
                */
                f32 _width;

                /**
                 * @brief tile height
                */
                f32 _height;

                /**
                 * @brief Tile texture top right point coordinates
                */
                Vec2f _textureCordsTopRight;

                /**
                 * @brief Tile texture bottom right point coordinates
                */
                Vec2f _textureCordsBottomRight;

                /**
                 * @brief Tile texture bottom left point coordinates
                */
                Vec2f _textureCordsBottomLeft;

                /**
                 * @brief Tile texture top left point coordinates
                */
                Vec2f _textureCordsTopLeft;
            };
            
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
