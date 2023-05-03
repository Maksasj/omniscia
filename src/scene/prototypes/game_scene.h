#ifndef _GAME_SCENE_
#define _GAME_SCENE_

#include "level_asset_manager.h"
#include "entity_prototypes.h"
#include "scene_loader.h"
#include "scene.h"

namespace omniscia::core {
    class GameScene : public Scene {
        public:
            GameScene() : Scene() {
                LevelAssetManager::get_instance().get("test_level")->load_asset(*this);

                add_dynamic_entity<Crab>();
                add_dynamic_entity<Player>();
                add_dynamic_entity<Grandpa>();
                add_static_entity<BeachParallaxBackground>();

                add_static_entity<Checkpoint>();

                unbind();
            }
    };
}

#endif