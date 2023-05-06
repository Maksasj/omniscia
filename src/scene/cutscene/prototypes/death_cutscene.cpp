#include "death_cutscene.h"

omniscia::core::DeathCutscene::DeathCutscene(Shader* transitionStageShader) 
    : Cutscene({
        CE_Step {
            new CE_SceneLoadCheckpointEvent((CE_SceneLoadCheckpointProp){})
        },
}) {}
