#ifndef _SCENE_LOAD_CHECKPOINT_CUTSCENE_
#define _SCENE_LOAD_CHECKPOINT_CUTSCENE_

#include "cutscene_step.h"
#include "cutscene_events_prototypes.h"

namespace omniscia::core {
    class LoadCheckpointCutscene : public Cutscene {
        public:
            LoadCheckpointCutscene(Shader* transitionStageShader);
    };
}

#endif
