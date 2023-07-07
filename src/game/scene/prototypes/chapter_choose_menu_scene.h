#ifndef _CHAPTER_CHOOSE_MENU_SCENE_
#define _CHAPTER_CHOOSE_MENU_SCENE_

#include "ecs/prototypes/entity_prototypes.h"
#include "scene/scene_loader/scene_loader.h"
#include "game.h"
#include "scene/scene.h"

namespace omniscia::core {
    using namespace omni::types;
    
    class ChapterChooseMenuScene : public Scene {
        public:
            ChapterChooseMenuScene();
    };
}

#endif