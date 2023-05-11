#ifndef _PAUSE_CUTSCENE_
#define _PAUSE_CUTSCENE_

#include "cutscene_step.h"
#include "cutscene_events_prototypes.h"

#include "endless_cutscene.h"

namespace omniscia::core {
    using namespace omni::types;
    
    class PauseCutscene : public EndlessCutscene {
        public:
            PauseCutscene(Shader* transitionStageShader);
    };
}

#endif
