#ifndef _SCENE_DIALOGUE_CUTSCENE_
#define _SCENE_DIALOGUE_CUTSCENE_

#include "cutscene_step.h"
#include "cutscene_events_prototypes.h"

namespace omniscia::core {
    class DialogueCutscene : public Cutscene {
        public:
            DialogueCutscene(Shader* transitionStageShader) : Cutscene({
                CE_Step {
                    new CE_Event((CE_Prop){ 
                        ._pauseBeforeStart = true,
                        ._pauseTimeBeforeStart = 8.0f,
                    })
                },
                CE_Step {
                    new CE_DisableSystemEvent<ECS_PlayerControllerSystem>((CE_DisableSystemProp){}),
                    new CE_DisableSystemEvent<ECS_PlayerJumpSystem>((CE_DisableSystemProp){}),
                    new CE_DisableSystemEvent<ECS_PlayerTimeJumpControllerSystem>((CE_DisableSystemProp){}),

                    new CE_SpawnDialogueTabEvent((CE_SpawnDialogueTabProp){
                        ._entityTmpName = "DialogueTab"
                    }),
                    new CE_SpawnDialogueTextEvent((CE_SpawnDialogueTextProp){
                        ._entityTmpName = "DialogueText"
                    }),
                    new CE_SpawnDialogueSpeakerIconEvent((CE_SpawnDialogueSpeakerIconProp) {
                        ._entityTmpName = "DialogueIcon",
                        ._speakerIconTextureId = "player_test_icon",
                    }),
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
                    }),
                    new CE_EntityTransparencyChangeEvent((CE_EntityTransparencyChangeProp) {
                        ._base = (CE_Prop){ ._durationTime = 0.5f },
                        ._entityTmpName = "DialogueTab",
                        ._startTransparency = 0.0f,
                        ._finishTransparency = 1.0f,
                        ._shapingFunction = &smoothstep<f32>,
                    }),
                    new CE_EntityTransparencyChangeEvent((CE_EntityTransparencyChangeProp) {
                        ._base = (CE_Prop){ ._durationTime = 0.5f },
                        ._entityTmpName = "DialogueIcon",
                        ._startTransparency = 0.0f,
                        ._finishTransparency = 1.0f,
                        ._shapingFunction = &smoothstep<f32>,
                    }),
                }, 
                CE_Step {
                    new CE_EntityPositionSetRelativeEvent((CE_EntityPositionSetRelativeProp) {
                        ._entityTmpName = "DialogueIcon",
                        ._relativePosition = Vec2f{1.2f, 0.0f},
                    }),
                    new CE_EntitySpriteFlipSetEvent((CE_EntitySpriteFlipSetProp) {
                        ._entityTmpName = "DialogueIcon",
                        ._verticalFlip = true,
                    }),
                    new CE_AnimateStaticTextEvent((CE_AnimateStaticTextProp) {
                        ._base = (CE_Prop){ ._durationTime = 1.5f },
                        ._entityTmpName = "DialogueText",
                        ._startingCharacterCount = 0,
                        ._finishCharacterCount = 18,
                        ._text = "Hello i am text",
                        ._shapingFunction = &smoothstep<f32>,
                    })
                },
                CE_Step {
                    new CE_AnimateStaticTextEvent((CE_AnimateStaticTextProp) {
                        ._base = (CE_Prop){ ._durationTime = 1.5f },
                        ._entityTmpName = "DialogueText",
                        ._startingCharacterCount = 18,
                        ._finishCharacterCount = 0,
                        ._text = "Hello i am text",
                        ._shapingFunction = &smoothstep<f32>,
                    })
                },
                CE_Step {
                    new CE_AnimateStaticTextEvent((CE_AnimateStaticTextProp) {
                        ._base = (CE_Prop){ ._durationTime = 1.5f },
                        ._entityTmpName = "DialogueText",
                        ._startingCharacterCount = 0,
                        ._finishCharacterCount = 23,
                        ._text = "Also i am animated text",
                        ._shapingFunction = &smoothstep<f32>,
                    })
                },
                CE_Step {
                    new CE_AnimateStaticTextEvent((CE_AnimateStaticTextProp) {
                        ._base = (CE_Prop){ ._durationTime = 1.5f },
                        ._entityTmpName = "DialogueText",
                        ._startingCharacterCount = 23,
                        ._finishCharacterCount = 0,
                        ._text = "Also i am animated text",
                        ._shapingFunction = &smoothstep<f32>,
                    })
                },
                CE_Step {
                    new CE_AnimateStaticTextEvent((CE_AnimateStaticTextProp) {
                        ._base = (CE_Prop){ ._durationTime = 1.5f },
                        ._entityTmpName = "DialogueText",
                        ._startingCharacterCount = 0,
                        ._finishCharacterCount = 57,
                        ._text = "btw, text also can be multy lined, for example like there",
                        ._shapingFunction = &smoothstep<f32>,
                    })
                }
            }) {}
    };
}

#endif
