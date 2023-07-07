#include "scene_transition_cutscene.h"

omniscia::core::TransitionCutscene::TransitionCutscene(Shader* transitionStageShader, const std::string& _sceneId) 
    : Cutscene({
        CE_Step {
            new CE_DisableSystemEvent<ECS_ButtonSystem>((CE_DisableSystemProp){}),
        },
        CE_Step {
            new CE_ShaderUniformF32ChangeEvent((CE_ShaderUniformF32ChangeProp){ 
                ._base = (CE_Prop){
                    ._durationTime = 1.5f
                },

                ._uniformName = "transitionSideProgress",
                ._shader = transitionStageShader,
                ._lambda = [](const f32& duration) {
                    f32 time = duration / 1.5f;
                    return time;
                }
            })
        },
        CE_Step {
            new CE_SceneSwitchEvent((CE_SceneSwitchProp){ 
                ._sceneName = _sceneId.c_str(),
            })
        },
        CE_Step {
            new CE_RunCutsceneCutsceneEvent((CE_RunCutsceneCutsceneProp){
                ._cutsceneId = "scene_save_checkpoint_cutscene"
            })
        },
        CE_Step{
            new CE_ShaderUniformF32ChangeEvent((CE_ShaderUniformF32ChangeProp){ 
                ._base = (CE_Prop){
                    ._durationTime = 1.5f
                },

                ._uniformName = "transitionSideProgress",
                ._shader = transitionStageShader,
                ._lambda = [](const f32& duration) {
                    f32 time = 1.0f - (duration / 1.5f);
                    return time;
                }
            })
        },                
        CE_Step {
            new CE_EnableSystemEvent<ECS_ButtonSystem>((CE_EnableSystemProp){}),
        }
}) {}
