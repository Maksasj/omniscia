#include "chapter_1_end_cutscene.h"

omniscia::core::Chapter1EndCutscene::Chapter1EndCutscene(Shader* transitionStageShader) 
    : Cutscene ({
        CE_Step {
            new CE_DisableSystemEvent<ECS_PlayerControllerSystem>(           (CE_DisableSystemProp){}),
            new CE_DisableSystemEvent<ECS_SpriteAnimationSystem>(            (CE_DisableSystemProp){}),
            new CE_DisableSystemEvent<ECS_AABBColliderSystem>(               (CE_DisableSystemProp){}),
            new CE_DisableSystemEvent<ECS_2DPhysicsRigidbodySystem>(         (CE_DisableSystemProp){}),
            new CE_DisableSystemEvent<ECS_GravitySystem>(                    (CE_DisableSystemProp){}),
            new CE_DisableSystemEvent<ECS_CameraFollowSystem>(               (CE_DisableSystemProp){}),
            new CE_DisableSystemEvent<ECS_PlayerJumpSystem>(                 (CE_DisableSystemProp){}),
            new CE_DisableSystemEvent<ECS_PlayerDebugMetricsSystem>(         (CE_DisableSystemProp){}),
            new CE_DisableSystemEvent<ECS_StateMachineBaseSystem>(           (CE_DisableSystemProp){}),
            new CE_DisableSystemEvent<ECS_SoundEmitterSystem>(               (CE_DisableSystemProp){}),
            new CE_DisableSystemEvent<ECS_PlayerTimeJumpControllerSystem>(   (CE_DisableSystemProp){}),
            new CE_DisableSystemEvent<ECS_ButtonSystem>(                     (CE_DisableSystemProp){}),
            new CE_DisableSystemEvent<ECS_InteractiveSystem>(                (CE_DisableSystemProp){}),
            new CE_DisableSystemEvent<ECS_DeadlySystem>(                     (CE_DisableSystemProp){}),
        },
        CE_Step{
            new CE_CameraZoomEvent((CE_CameraZoomProp){ 
                ._base = (CE_Prop){ ._durationTime = 2.5f },
                ._startZoom = 1.0f,
                ._finishZoom = 1.6f,
                ._shapingFunction = &smoothstep<f32>,
            }),
            new CE_ShaderUniformF32ChangeEvent((CE_ShaderUniformF32ChangeProp){ 
                ._base = (CE_Prop){
                    ._pauseBeforeStart = true,
                    ._pauseTimeBeforeStart = 0.5f,
                    ._durationTime = 3.5f
                },
                ._uniformName = "transitionChapterCircleProgress",
                ._shader = transitionStageShader,
                ._lambda = [](const f32& duration) {
                    return smoothstep(0.0f, 0.7f, (duration / 3.5f));;
                }
            }),
        },
        CE_Step {
            new CE_ShaderUniformF32ChangeEvent((CE_ShaderUniformF32ChangeProp){ 
                ._base = (CE_Prop){
                    ._pauseBeforeStart = true,
                    ._pauseTimeBeforeStart = 1.0f,
                    ._durationTime = 1.5f,
                },

                ._uniformName = "transitionChapterCircleProgress",
                ._shader = transitionStageShader,
                ._lambda = [](const f32& duration) {
                    return smoothstep(0.7f, 1.1f, (duration / 1.5f));;
                }
            }),
        },
        CE_Step {
            new CE_EnableSystemEvent<ECS_PlayerControllerSystem>(           (CE_EnableSystemProp){}),
            new CE_EnableSystemEvent<ECS_SpriteAnimationSystem>(            (CE_EnableSystemProp){}),
            new CE_EnableSystemEvent<ECS_AABBColliderSystem>(               (CE_EnableSystemProp){}),
            new CE_EnableSystemEvent<ECS_2DPhysicsRigidbodySystem>(         (CE_EnableSystemProp){}),
            new CE_EnableSystemEvent<ECS_GravitySystem>(                    (CE_EnableSystemProp){}),
            new CE_EnableSystemEvent<ECS_CameraFollowSystem>(               (CE_EnableSystemProp){}),
            new CE_EnableSystemEvent<ECS_PlayerJumpSystem>(                 (CE_EnableSystemProp){}),
            new CE_EnableSystemEvent<ECS_PlayerDebugMetricsSystem>(         (CE_EnableSystemProp){}),
            new CE_EnableSystemEvent<ECS_StateMachineBaseSystem>(           (CE_EnableSystemProp){}),
            new CE_EnableSystemEvent<ECS_SoundEmitterSystem>(               (CE_EnableSystemProp){}),
            new CE_EnableSystemEvent<ECS_PlayerTimeJumpControllerSystem>(   (CE_EnableSystemProp){}),
            new CE_EnableSystemEvent<ECS_ButtonSystem>(                     (CE_EnableSystemProp){}),
            new CE_EnableSystemEvent<ECS_InteractiveSystem>(                (CE_EnableSystemProp){}),
            new CE_EnableSystemEvent<ECS_DeadlySystem>(                     (CE_EnableSystemProp){}),
        },
}) {}
