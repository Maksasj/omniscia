#include "scene_load_checkpoint_cutscene.h"

omniscia::core::LoadCheckpointCutscene::LoadCheckpointCutscene(Shader* transitionStageShader) 
    : Cutscene({
        CE_Step {
            new CE_SceneLoadCheckpointEvent((CE_SceneLoadCheckpointProp){})
        },
        CE_Step {
            new CE_ReduceTimelineFramesEvent((CE_ReduceTimelineFramesProp) {}),
        }
}) {}

