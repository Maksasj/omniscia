#ifndef _SETTINGS_SCENE_
#define _SETTINGS_SCENE_

#include "entity_prototypes.h"
#include "scene_loader.h"
#include "scene.h"

namespace omniscia::core {
    class SettingsScene : public Scene {
        public:
            SettingsScene() : Scene() {
                add_static_entity<BeachParallaxBackground>();
                unbind();
            }
    };
}

#endif