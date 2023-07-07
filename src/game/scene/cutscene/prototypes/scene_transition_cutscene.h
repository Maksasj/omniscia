#ifndef _SCENE_TRANSITION_CUTSCENE_
#define _SCENE_TRANSITION_CUTSCENE_

#include "scene/cutscene/cutscene_step.h"
#include "scene/cutscene/cutscene_events_prototypes.h"

namespace omniscia::core {
    using namespace omni::types;
    
    class TransitionCutscene : public Cutscene {
        public:
            TransitionCutscene(Shader* transitionStageShader, const std::string& _sceneId);
    };
}

#endif
