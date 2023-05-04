#include "use_checkpoint_cutscene.h"

omniscia::core::UseCheckpointCutscene::UseCheckpointCutscene(Shader* transitionStageShader) 
    : Cutscene({
        CE_Step {
            new CE_SceneSaveCheckpointEvent((CE_SceneSaveCheckpointProp){})
        },
}) {}
