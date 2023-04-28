#ifndef _SCENE_DIALOGUE_CUTSCENE_
#define _SCENE_DIALOGUE_CUTSCENE_

#include "cutscene_step.h"
#include "cutscene_events_prototypes.h"

namespace omniscia::core {
    class DialogueCutscene : public Cutscene {
        public:
            DialogueCutscene(Shader* transitionStageShader) : Cutscene({
                CE_Step{
                    new CE_Event((CE_Prop){ 
                        ._pauseBeforeStart = true,
                        ._pauseTimeBeforeStart = 8.0f,
                    })
                },
                CE_Step {
                    new CE_DisableSystemEvent<ECS_PlayerControllerSystem>((CE_DisableSystemProp){}),
                    new CE_DisableSystemEvent<ECS_PlayerJumpSystem>((CE_DisableSystemProp){}),
                },
                CE_Step {
                    new CE_CameraZoomEvent((CE_CameraZoomProp){ 
                        ._base = (CE_Prop){ ._durationTime = 1.5f },
                        ._startZoom = 1.0f,
                        ._finishZoom = 1.5f,
                        ._shapingFunction = &smoothstep<f32>,
                    }),
                    new CE_ShaderUniformF32ChangeEvent((CE_ShaderUniformF32ChangeProp){ 
                        ._base = (CE_Prop){ ._durationTime = 1.5f },
                        ._uniformName = "letterBoxLowerBound",
                        ._shader = transitionStageShader,
                        ._lambda = [](const f32& duration) { return smoothstep(0.0f, 1.0f, duration / 1.5f) * 0.1f; }
                    }),
                    new CE_ShaderUniformF32ChangeEvent((CE_ShaderUniformF32ChangeProp){ 
                        ._base = (CE_Prop){ ._durationTime = 1.5f },
                        ._uniformName = "letterBoxUpperBound",
                        ._shader = transitionStageShader,
                        ._lambda = [](const f32& duration) { return smoothstep(0.0f, 1.0f, duration / 1.5f) * 0.1f; }
                    })
                }, 
                CE_Step {
                    new CE_ShowDialogueTabEvent((CE_ShowDialogueTabProp){}),
                }
            }) {}
    };
}

#endif
