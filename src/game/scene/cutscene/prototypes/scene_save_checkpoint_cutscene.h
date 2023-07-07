#ifndef _SCENE_SAVE_CHECKPOINT_CUTSCENE_
#define _SCENE_SAVE_CHECKPOINT_CUTSCENE_

#include "cutscene_step.h"
#include "cutscene_events_prototypes.h"

namespace omniscia::core {
    using namespace omni::types;
    
    class SaveCheckpointCutscene : public Cutscene {
        public:
            SaveCheckpointCutscene(Shader* transitionStageShader);
    };
}

#endif
