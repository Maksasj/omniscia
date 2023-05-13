#ifndef _GAME_SCENE_
#define _GAME_SCENE_

#include "level_asset_manager.h"
#include "entity_prototypes.h"
#include "scene_loader.h"
#include "scene.h"

namespace omniscia::core {
    using namespace omni::types;
    
    class GameScene : public Scene {
        public:
            GameScene() : Scene() {
                LevelAssetManager::get_instance().get("test_level")->load_asset(*this);

                summon_dynamic_entity_at_marker_group<Player>(0);
                summon_static_entity_at_marker_group<Checkpoint>(1);
                summon_static_entity_at_marker_group<Star>(2);

                // add_dynamic_entity<Crab>();
                // add_dynamic_entity<Player>();
                add_dynamic_entity<Grandpa>(Vec2f{1.0f, 1.0f});
                add_static_entity<BeachParallaxBackground>();
// 
                // add_static_entity<Checkpoint>();

                unbind();
            }
    };
}

#endif