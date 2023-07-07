#ifndef _USE_CHECKPOINT_CUTSCENE_
#define _USE_CHECKPOINT_CUTSCENE_

#include "scene/cutscene/cutscene_step.h"
#include "scene/cutscene/cutscene_events_prototypes.h"

namespace omniscia::core {
    using namespace omni::types;
    
    class UseCheckpointCutscene : public Cutscene {
        public:
            UseCheckpointCutscene(Shader* transitionStageShader);
    };
}

#endif
