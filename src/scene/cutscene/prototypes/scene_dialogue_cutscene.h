#ifndef _SCENE_DIALOGUE_CUTSCENE_
#define _SCENE_DIALOGUE_CUTSCENE_

#include "cutscene_step.h"
#include "cutscene_events_prototypes.h"

namespace omniscia::core {
    struct DialogueStepData {
        std::string _speakerIconTexture;
        i32 _side;
        std::string _text;

        DialogueStepData(const std::string& speakerIconTexture, const i32& side, const std::string& text) {
            _speakerIconTexture = speakerIconTexture;
            _side = side;
            _text = text;
        }
    };

    class DialogueCutscene : public Cutscene {
        public:
            DialogueCutscene(Shader* transitionStageShader, const std::vector<DialogueStepData> dialogueData) : Cutscene({
                CE_Step {
                    new CE_DisableSystemEvent<ECS_PlayerControllerSystem>((CE_DisableSystemProp){}),
                    new CE_DisableSystemEvent<ECS_PlayerJumpSystem>((CE_DisableSystemProp){}),
                    new CE_DisableSystemEvent<ECS_PlayerTimeJumpControllerSystem>((CE_DisableSystemProp){}),
                    new CE_DisableSystemEvent<ECS_InteractiveSystem>((CE_DisableSystemProp){}),

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
                    new CE_EntityPositionSetRelativeEvent((CE_EntityPositionSetRelativeProp) {
                        ._entityTmpName = "DialogueIcon",
                        ._relativePosition = Vec2f{((dialogueData[0]._side == 1) ? 0.6f : -0.6f), 0.3f},
                    }),
                    new CE_EntityPositionSetRelativeEvent((CE_EntityPositionSetRelativeProp) {
                        ._entityTmpName = "DialogueText",
                        ._relativePosition = Vec2f{((dialogueData[0]._side == 1) ? 0.1f : -0.2f), 0.3f},
                    }),
                    new CE_EntityPositionSetRelativeEvent((CE_EntityPositionSetRelativeProp) {
                        ._entityTmpName = "DialogueTab",
                        ._relativePosition = Vec2f{0.0f, 0.3f},
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
                },
                CE_MultiStep<DialogueStepData>(dialogueData.size(), dialogueData, [](const DialogueStepData& stepData) {
                    return (std::vector<CE_Step>){ 
                        CE_Step {
                            new CE_EntityTransparencyChangeEvent((CE_EntityTransparencyChangeProp) {
                                ._base = (CE_Prop){ ._durationTime = 0.1f },
                                ._entityTmpName = "DialogueIcon",
                                ._startTransparency = 0.0f,
                                ._finishTransparency = 1.0f,
                                ._shapingFunction = &smoothstep<f32>,
                            }),
                            new CE_EntitySpriteFlipSetEvent((CE_EntitySpriteFlipSetProp) {
                                ._entityTmpName = "DialogueIcon",
                                ._verticalFlip = ((stepData._side == 1) ? false : true),
                            }),
                            new CE_EntitySpriteRendererSetTextureEvent((CE_EntitySpriteRendererSetTextureProp) {
                                ._entityTmpName = "DialogueIcon",
                                ._textureId = stepData._speakerIconTexture
                            }),
                            new CE_EntityPositionSetRelativeEvent((CE_EntityPositionSetRelativeProp) {
                                ._entityTmpName = "DialogueIcon",
                                ._relativePosition = Vec2f{((stepData._side == 1) ? -0.6f : 0.6f), 0.3f},
                            }),
                            new CE_EntityPositionSetRelativeEvent((CE_EntityPositionSetRelativeProp) {
                                ._entityTmpName = "DialogueText",
                                ._relativePosition = Vec2f{((stepData._side == 1) ? 0.1f : -0.2f), 0.3f},
                            }),
                        },
                        CE_Step {
                            new CE_AnimateStaticTextEvent((CE_AnimateStaticTextProp) {
                                ._base = (CE_Prop){ 
                                    ._pauseAfterFinishing = true,
                                    ._pauseTimeAfterFinishing = 0.8f,
                                    ._durationTime = 1.5f,
                                },
                                ._entityTmpName = "DialogueText",
                                ._startingCharacterCount = 0,
                                ._finishCharacterCount = stepData._text.size(),
                                ._text = stepData._text,
                                ._shapingFunction = &smoothstep<f32>,
                            })
                        },
                        CE_Step {
                            new CE_AnimateStaticTextEvent((CE_AnimateStaticTextProp) {
                                ._base = (CE_Prop){ 
                                    ._pauseAfterFinishing = true,
                                    ._pauseTimeAfterFinishing = 0.8f,
                                    ._durationTime = 1.5f ,
                                },
                                ._entityTmpName = "DialogueText",
                                ._startingCharacterCount = stepData._text.size(),
                                ._finishCharacterCount = 0,
                                ._text = stepData._text,
                                ._shapingFunction = &smoothstep<f32>,
                            }),
                        },
                        CE_Step {
                            new CE_EntityTransparencyChangeEvent((CE_EntityTransparencyChangeProp) {
                                ._base = (CE_Prop){ ._durationTime = 0.1f },
                                ._entityTmpName = "DialogueIcon",
                                ._startTransparency = 1.0f,
                                ._finishTransparency = 0.0f,
                                ._shapingFunction = &smoothstep<f32>,
                            }),
                        }
                    };
                }),
                CE_Step {
                    new CE_CameraZoomEvent((CE_CameraZoomProp){ 
                        ._base = (CE_Prop){ ._durationTime = 1.5f },
                        ._startZoom = 1.5f,
                        ._finishZoom = 1.0f,
                        ._shapingFunction = &smoothstep<f32>,
                    }),
                    new CE_ShaderUniformF32ChangeEvent((CE_ShaderUniformF32ChangeProp){ 
                        ._base = (CE_Prop){ ._durationTime = 1.5f },
                        ._uniformName = "letterBoxLowerBound",
                        ._shader = transitionStageShader,
                        ._lambda = [](const f32& duration) { return smoothstep(1.0f, 0.0f, duration / 1.5f) * 0.1f; }
                    }),
                    new CE_ShaderUniformF32ChangeEvent((CE_ShaderUniformF32ChangeProp){ 
                        ._base = (CE_Prop){ ._durationTime = 1.5f },
                        ._uniformName = "letterBoxUpperBound",
                        ._shader = transitionStageShader,
                        ._lambda = [](const f32& duration) { return smoothstep(1.0f, 0.0f, duration / 1.5f) * 0.1f; }
                    }),
                    new CE_EntityTransparencyChangeEvent((CE_EntityTransparencyChangeProp) {
                        ._base = (CE_Prop){ ._durationTime = 0.5f },
                        ._entityTmpName = "DialogueTab",
                        ._startTransparency = 1.0f,
                        ._finishTransparency = 0.0f,
                        ._shapingFunction = &smoothstep<f32>,
                    }),
                },
                CE_Step {
                    new CE_EnableSystemEvent<ECS_PlayerControllerSystem>((CE_EnableSystemProp){}),
                    new CE_EnableSystemEvent<ECS_PlayerJumpSystem>((CE_EnableSystemProp){}),
                    new CE_EnableSystemEvent<ECS_PlayerTimeJumpControllerSystem>((CE_EnableSystemProp){}),
                    new CE_EnableSystemEvent<ECS_InteractiveSystem>((CE_EnableSystemProp){}),

                    new CE_DestroyEntityEvent((CE_DestroyEntityProp) { ._entityTmpName = "DialogueTab" }),
                    new CE_DestroyEntityEvent((CE_DestroyEntityProp) { ._entityTmpName = "DialogueText" }),
                    new CE_DestroyEntityEvent((CE_DestroyEntityProp) { ._entityTmpName = "DialogueIcon", }),
                },
            }) {}
    };
}

#endif
