#include "scene_save_checkpoint_cutscene.h"

omniscia::core::SaveCheckpointCutscene::SaveCheckpointCutscene(Shader* transitionStageShader) 
    : Cutscene({
        CE_Step {
            new CE_SceneSaveCheckpointEvent((CE_SceneSaveCheckpointProp){})
        },
}) {}
