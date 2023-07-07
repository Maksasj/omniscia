#ifndef _PAUSE_CUTSCENE_
#define _PAUSE_CUTSCENE_

#include "scene/cutscene/cutscene_step.h"
#include "scene/cutscene/cutscene_events_prototypes.h"

#include "scene/cutscene/endless_cutscene.h"

namespace omniscia::core {
    using namespace omni::types;
    
    class PauseCutscene : public EndlessCutscene {
        public:
            PauseCutscene(Shader* transitionStageShader);
    };
}

#endif
