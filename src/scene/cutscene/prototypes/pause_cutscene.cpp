#include "pause_cutscene.h"

omniscia::core::PauseCutscene::PauseCutscene(Shader* transitionStageShader) 
    : EndlessCutscene({
        // Wait before pause screen
        CE_Step {
            new CE_WaitCutsceneEvent((CE_WaitCutsceneProp){
                ._lambda = []() {
                    return Controls::get_instance().get(PlayerController::PAUSE);
                }
            }),
        },
        CE_Step {
            new CE_SpawnPauseTextEvent((CE_SpawnPauseTextProp) {
                ._entityTmpName = "pauseTextEntity",
            }),
        },
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
            new CE_ShaderUniformF32ChangeEvent((CE_ShaderUniformF32ChangeProp){ 
                ._base = (CE_Prop){
                    ._durationTime = 0.3f
                },

                ._uniformName = "shadowTintStrength",
                ._shader = transitionStageShader,
                ._lambda = [](const f32& duration) {
                    const f32 time = 0.8f * (duration / 0.3f);
                    return time;
                }
            }),
            new CE_EntityTransparencyChangeEvent((CE_EntityTransparencyChangeProp) {
                ._base = (CE_Prop){ ._durationTime = 0.3f },
                ._entityTmpName = "pauseTextEntity",
                ._startTransparency = 0.0f,
                ._finishTransparency = 1.0f,
                ._shapingFunction = &smoothstep<f32>,
            }),
        },
        // Wait until unpause, unpause
        CE_Step {
            new CE_WaitCutsceneEvent((CE_WaitCutsceneProp){
                ._lambda = []() {
                    return Controls::get_instance().get(PlayerController::PAUSE);
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
        CE_Step {
            new CE_DestroyEntityEvent((CE_DestroyEntityProp) { ._entityTmpName = "pauseTextEntity" }),
        },
        CE_Step {
            new CE_ShaderUniformF32ChangeEvent((CE_ShaderUniformF32ChangeProp){ 
                ._base = (CE_Prop){
                    ._durationTime = 0.3f
                },

                ._uniformName = "shadowTintStrength",
                ._shader = transitionStageShader,
                ._lambda = [](const f32& duration) {
                    const f32 time = 1.0f - 0.8f * (duration / 0.3f);
                    return time;
                }
            }),
            new CE_EntityTransparencyChangeEvent((CE_EntityTransparencyChangeProp) {
                ._base = (CE_Prop){ ._durationTime = 0.3f },
                ._entityTmpName = "pauseTextEntity",
                ._startTransparency = 1.0f,
                ._finishTransparency = 0.0f,
                ._shapingFunction = &smoothstep<f32>,
            }),
        },
}) {}
