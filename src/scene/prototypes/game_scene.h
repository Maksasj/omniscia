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

                summon_static_entity_at_marker_group<Player>(0);
                summon_static_entity_at_marker_group<Checkpoint>(1);
                summon_static_entity_at_marker_group<Star>(2);
                
                summon_dynamic_entity_at_marker_group<Crab>(3);

                summon_static_entity_at_marker_group<RedCrystal>(4);

                add_dynamic_entity<Grandpa>(Vec2f{1.0f, 1.0f});
                add_static_entity<BeachParallaxBackground>();

                add_static_entity<AnimatedImage>((AnimatedImageProp){
                    ._texture = "star-spritesheet",
                    ._animation = "star-shiny-animation",
                    ._layer = 11,
                    ._pos = Vec2f{1.4f, 0.85f},
                    ._scale = Vec2f{0.1f, 0.1f},
                });
                
                add_static_entity<CollectedText>(Vec2f{1.75f, 0.87f}, Vec2f{0.1f, 0.1f}, (CollectedTextProp){
                    ._fontId = "monogram-white",
                    ._textToRender = "x5",
                    ._lineLetterSpacing = 0.31f,
                    ._rowLineSpacing = 0.0f,
                    ._charactersPerRow = 3u,
                });

                add_static_entity<ClockProgressionBar>((ClockProgressionBarProp){
                    ._texture = "clock-bar-spritesheet",
                    ._animation = "clock-bar-progression-animation",
                    ._layer = 11,
                    ._pos = Vec2f{-1.45f, 0.85f},
                    ._scale = Vec2f{0.1f, 0.1f},
                });

                unbind();
            }
    };
}

#endif