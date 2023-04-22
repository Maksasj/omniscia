#ifndef _GAME_SCENE_
#define _GAME_SCENE_

#include "prototypes.h"
#include "scene.h"

namespace omniscia::core {
    class GameScene : public Scene {
        public:
            GameScene() : Scene() {
                SceneLoader::get_instance().load_scene(*this);
                add_dynamic_entity<Crab>();
                add_dynamic_entity<Player>();
                add_dynamic_entity<Grandpa>();
                add_static_entity<BeachParallaxBackground>();
                unbind();
            }
    };
}

#endif