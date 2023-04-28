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

                add_static_entity<StaticText>(Vec2f{0.0f, 0.8f}, Vec2f{0.03f, 0.03f}, (StaticTextProp) {
                    ._fontId = "test_font",
                    ._textToRender = "Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum.",
                    ._lineLetterSpacing = 0.3f,
                    ._rowLineSpacing = 0.7f,
                    ._charactersPerRow = 24u,
                });

                unbind();
            }
    };
}

#endif