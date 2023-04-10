#ifndef _SCENE_H_
#define _SCENE_H_

#include "types.tpp"
#include "player.h"

namespace omniscia::core {
    class Scene {
        public:
            struct SceneDynamic {
                std::vector<Entity> dynamicEntities;
            };

            struct SceneStatic {
                std::vector<Entity> staticEntities;
            };
        protected:
            SceneDynamic dynamicPart;
            SceneStatic staticPart;
        public:
            friend class SceneLoader;

            SceneDynamic clone();
            
            void unbind();
            void time_sync();

            SceneDynamic& ref_dynamic_part();
            SceneStatic& ref_static_part();

            template<class T>
            void add_dynamic_entity() {
                dynamicPart.dynamicEntities.push_back(T());
            }

            template<class T, class... Args>
            void add_dynamic_entity(Args&&... args) {
                dynamicPart.dynamicEntities.push_back(T(std::forward<Args>(args)...));
            }

            template<class T>
            void add_static_entity() {
                staticPart.staticEntities.push_back(T());
            }

            template<class T, class... Args>
            void add_static_entity(Args&&... args) {
                staticPart.staticEntities.push_back(T(std::forward<Args>(args)...));
            }
    };
}

#endif
