#ifndef _DEATH_CUTSCENE_
#define _DEATH_CUTSCENE_

#include "scene/cutscene/cutscene_step.h"
#include "scene/cutscene/cutscene_events_prototypes.h"

namespace omniscia::core {
    using namespace omni::types;
    
    class DeathCutscene : public Cutscene {
        public:
            DeathCutscene(Shader* transitionStageShader);
    };
}

#endif
