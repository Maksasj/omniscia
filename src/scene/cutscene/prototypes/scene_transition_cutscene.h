#ifndef _SCENE_TRANSITION_CUTSCENE_
#define _SCENE_TRANSITION_CUTSCENE_

#include "cutscene_step.h"
#include "cutscene_events_prototypes.h"

namespace omniscia::core {
    class TransitionCutscene : public Cutscene {
        public:
            TransitionCutscene(Shader* transitionStageShader, const std::string& _sceneId);
    };
}

#endif
