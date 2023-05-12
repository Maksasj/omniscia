#include "death_cutscene.h"

omniscia::core::DeathCutscene::DeathCutscene(Shader* transitionStageShader) 
    : Cutscene({
        CE_Step {
            new CE_DisableSystemEvent<ECS_PlayerControllerSystem>((CE_DisableSystemProp){}),
            new CE_DisableSystemEvent<ECS_PlayerJumpSystem>((CE_DisableSystemProp){}),
            new CE_DisableSystemEvent<ECS_PlayerTimeJumpControllerSystem>((CE_DisableSystemProp){}),
            new CE_DisableSystemEvent<ECS_InteractiveSystem>((CE_DisableSystemProp){}),
            new CE_DisableSystemEvent<ECS_DeadlySystem>((CE_DisableSystemProp){}),
            new CE_FindDynamicEntityEvent<Player>((CE_IndexDynamicEntityProp){
                ._entityTmpName = "Player",
            }),
        },
        CE_Step {
            new CE_EntitySpriteAnimationSetAnimationEvent((CE_EntitySpriteAnimationSetAnimationProp){
                ._base = (CE_Prop){ 
                    ._pauseAfterFinishing = true,
                    ._pauseTimeAfterFinishing = 1.0f,
                },
                ._entityTmpName = "Player",
                ._animationId = "player-death-animation",
            }),
        },
        CE_Step {
            new CE_ShaderUniformF32ChangeEvent((CE_ShaderUniformF32ChangeProp){ 
                ._base = (CE_Prop){ ._durationTime = 1.0f },
                ._uniformName = "transitionCircleProgress",
                ._shader = transitionStageShader,
                ._lambda = [](const f32& duration) { return smoothstep(0.0f, 1.1f, duration / 1.0f); }
            }),
        },
        CE_Step {
            new CE_SceneLoadCheckpointEvent((CE_SceneLoadCheckpointProp){})
        },
        CE_Step {
            new CE_EnableSystemEvent<ECS_PlayerControllerSystem>((CE_EnableSystemProp){}),
            new CE_EnableSystemEvent<ECS_PlayerJumpSystem>((CE_EnableSystemProp){}),
            new CE_EnableSystemEvent<ECS_PlayerTimeJumpControllerSystem>((CE_EnableSystemProp){}),
            new CE_EnableSystemEvent<ECS_InteractiveSystem>((CE_EnableSystemProp){}),
            new CE_EnableSystemEvent<ECS_DeadlySystem>((CE_EnableSystemProp){}),
        },
        CE_Step {
            new CE_ShaderUniformF32ChangeEvent((CE_ShaderUniformF32ChangeProp){ 
                ._base = (CE_Prop){ ._durationTime = 1.0f },
                ._uniformName = "transitionCircleProgress",
                ._shader = transitionStageShader,
                ._lambda = [](const f32& duration) { return smoothstep(1.1f, 0.0f, duration / 1.0f); }
            }),
        },
}) {}
