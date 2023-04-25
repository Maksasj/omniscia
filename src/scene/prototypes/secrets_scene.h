#ifndef _SECRETS_SCENE_
#define _SECRETS_SCENE_

#include "entity_prototypes.h"
#include "scene_loader.h"
#include "scene.h"

namespace omniscia::core {
    class SecretsScene : public Scene {
        public:
            SecretsScene() : Scene() {
                add_static_entity<Background>((BackgroundProp) {
                    ._texture = "secrets_background",
                    ._layer = 0,
                });
                
                unbind();
            }
    };
}

#endif