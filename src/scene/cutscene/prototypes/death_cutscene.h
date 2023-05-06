#ifndef _DEATH_CUTSCENE_
#define _DEATH_CUTSCENE_

#include "cutscene_step.h"
#include "cutscene_events_prototypes.h"

namespace omniscia::core {
    using namespace omni::types;
    
    class DeathCutscene : public Cutscene {
        public:
            DeathCutscene(Shader* transitionStageShader);
    };
}

#endif
