#ifndef _SECRETS_SCENE_
#define _SECRETS_SCENE_

#include "ecs/prototypes/entity_prototypes.h"
#include "scene/scene_loader/scene_loader.h"
#include "scene/scene.h"

namespace omniscia::core {
    using namespace omni::types;
    
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