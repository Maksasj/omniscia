#ifndef _SCENE_TRANSITION_CUTSCENE_
#define _SCENE_TRANSITION_CUTSCENE_

#include "cutscene.h"

namespace omniscia::core {
    class TransitionCutscene : public Cutscene {
        public:
            TransitionCutscene(Shader* transitionStageShader, const std::string& _sceneId) : Cutscene({
                CE_Step{
                    new CE_ShaderUniformF32ChangeEvent((CE_ShaderUniformF32ChangeProp){ 
                        ._base = (CE_Prop){
                            ._durationTime = 1.5f
                        },

                        ._uniformName = "time",
                        ._shader = transitionStageShader,
                        ._lambda = [](const f32& duration) {
                            f32 time = duration / 1.5f;
                            return time;
                        }
                    })
                },
                CE_Step{
                    new CE_SceneSwitchEvent((CE_SceneSwitchProp){ 
                        ._sceneName = _sceneId.c_str(),
                    })
                },
                CE_Step{
                    new CE_ShaderUniformF32ChangeEvent((CE_ShaderUniformF32ChangeProp){ 
                        ._base = (CE_Prop){
                            ._durationTime = 1.5f
                        },

                        ._uniformName = "time",
                        ._shader = transitionStageShader,
                        ._lambda = [](const f32& duration) {
                            f32 time = 1.0f - (duration / 1.5f);
                            return time;
                        }
                    })
                }
            }) {}
    };
}

#endif
