#ifndef _ENTITY_TRANSPARENCY_CHANGE_EVENT_CUTSCENE_EVENT_
#define _ENTITY_TRANSPARENCY_CHANGE_EVENT_CUTSCENE_EVENT_

#include <functional>
#include <string>

#include "camera.h"
#include "cutscene_event.h"

namespace omniscia::core {
    using namespace omni::types;
    
    struct CE_EntityTransparencyChangeProp {
        CE_Prop _base;

        std::string _entityTmpName = "";
        f32 _startTransparency = 1.0f;
        f32 _finishTransparency = 1.0f;
        std::function<f32(const f32&, const f32&, const f32&)> _shapingFunction;
    };

    class CE_EntityTransparencyChangeEvent : public CE_EntityTransparencyChangeProp , public CE_Event {
        private:
            CE_EntityTransparencyChangeEvent();
            CE_EntityTransparencyChangeEvent(const CE_EntityTransparencyChangeEvent&);
            void operator=(const CE_EntityTransparencyChangeEvent&);

            void reset() override {
                reset_base();
            }

        public:
            CE_EntityTransparencyChangeEvent(const CE_EntityTransparencyChangeProp& data = CE_EntityTransparencyChangeProp{});
            
            void execute() override;
    };
}

#endif
