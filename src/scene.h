/**
 * @file 
 * scene.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _SCENE_H_
#define _SCENE_H_

#include "types.tpp"
#include "player.h"

namespace omniscia::core {
    /**
     * @brief Class that manages all scene data, dynamic and static part
    */
    class Scene {
        public:
            /**
             * @brief SceneDynamic - class that used for storing 
             * and managing all dynamic entities
            */
            struct SceneDynamic {
                std::vector<Entity> dynamicEntities;
            };

            /**
             * @brief SceneStatic - class that used for storing 
             * and managing all static entities
            */
            struct SceneStatic {
                std::vector<Entity> staticEntities;
            };

        protected:
            /**
             * @brief Instance of the SceneDynamic
            */
            SceneDynamic dynamicPart;
            
            /**
             * @brief Instance of the SceneStatic
            */
            SceneStatic staticPart;

        public:
            friend class SceneLoader;

            /**
             * @brief Method used for cloning dynamic scene part
             * 
             * @return SceneDynamic new dynamic scene part instance
            */
            SceneDynamic clone();

            /**
             * @brief Unbinds all components from all systems
            */
            void unbind();

            /**
             * @brief Binds all components to systems
            */
            void time_sync();

            /**
             * @brief Get reference to scene dynamic part
             * 
             * @return SceneDynamic& reference to dynamic scene part
            */
            SceneDynamic& ref_dynamic_part();

            /**
             * @brief Get reference to scene static part
             * 
             * @return SceneStatic& reference to static scene part
            */
            SceneStatic& ref_static_part();

            /**
             * @brief Adds entity as dynamic entity
             * 
             * @tparam T type of the entity
            */
            template<class T>
            void add_dynamic_entity() {
                dynamicPart.dynamicEntities.push_back(T());
            }

            /**
             * @brief Adds entity as dynamic entity
             * 
             * @tparam T type of the entity
             * @tparam Args type of the entity constructor arguments
             * @param args entity constructor arguments
            */
            template<class T, class... Args>
            void add_dynamic_entity(Args&&... args) {
                dynamicPart.dynamicEntities.push_back(T(std::forward<Args>(args)...));
            }

            /**
             * @brief Adds entity as static entity
             * 
             * @tparam T type of the entity
            */
            template<class T>
            void add_static_entity() {
                staticPart.staticEntities.push_back(T());
            }

            /**
             * @brief Adds entity as static entity
             * 
             * @tparam T type of the entity
             * @tparam Args type of the entity constructor arguments
             * @param args entity constructor arguments
            */
            template<class T, class... Args>
            void add_static_entity(Args&&... args) {
                staticPart.staticEntities.push_back(T(std::forward<Args>(args)...));
            }
    };
}

#endif
