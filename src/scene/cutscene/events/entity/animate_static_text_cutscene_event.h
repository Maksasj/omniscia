#ifndef _ANIMATE_STATIC_TEXT_EVENT_CUTSCENE_EVENT_
#define _ANIMATE_STATIC_TEXT_EVENT_CUTSCENE_EVENT_

#include <functional>
#include <string>

#include "camera.h"
#include "cutscene_event.h"

namespace omniscia::core {
    struct CE_AnimateStaticTextProp {
        CE_Prop _base;

        std::string _entityTmpName = "";

        i32 _startingCharacterCount = 0;
        i32 _finishCharacterCount = 0;
        std::string _text = "";
        
        std::function<f32(const f32&, const f32&, const f32&)> _shapingFunction;
    };

    class CE_AnimateStaticTextEvent : public CE_AnimateStaticTextProp , public CE_Event {
        private:
            CE_AnimateStaticTextEvent();
            CE_AnimateStaticTextEvent(const CE_AnimateStaticTextEvent&);
            void operator=(const CE_AnimateStaticTextEvent&);

        public:
            CE_AnimateStaticTextEvent(const CE_AnimateStaticTextProp& data = CE_AnimateStaticTextProp{});
            
            void execute() override;
    };
}

#endif
