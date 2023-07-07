#ifndef _SHADER_UNIFORM_CHANGE_CUTSCENE_EVENT_
#define _SHADER_UNIFORM_CHANGE_CUTSCENE_EVENT_

#include <string>
#include <functional>

#include "shader.h"
#include "cutscene_event.h"

namespace omniscia::core {
    using namespace omni::types;
    using namespace omniscia::gfx;

    struct CE_ShaderUniformF32ChangeProp {
        CE_Prop _base;

        const char* _uniformName = nullptr;
        Shader* _shader = nullptr;
        std::function<f32(const f32&)> _lambda = [](const f32&) { return 1.0f; };
    };
    
    class CE_ShaderUniformF32ChangeEvent : public CE_ShaderUniformF32ChangeProp, public CE_Event {
        private:
            CE_ShaderUniformF32ChangeEvent() {}
            CE_ShaderUniformF32ChangeEvent(const CE_ShaderUniformF32ChangeEvent&) {}
            void operator=(const CE_ShaderUniformF32ChangeEvent&) {}

            void reset() override {
                reset_base();
            }

        public:
            CE_ShaderUniformF32ChangeEvent(const CE_ShaderUniformF32ChangeProp& data = CE_ShaderUniformF32ChangeProp{}) : CE_ShaderUniformF32ChangeProp(data), CE_Event(*(CE_Prop*)&data) {
                
            }
            
            void execute() override {
                if(_shader == nullptr) 
                    return;

                _shader->set_uniform_f32(_uniformName, _lambda(get_current_duration()));
            }
    };
}

#endif
