#ifndef _DISABLE_SYSTEM_CUTSCENE_EVENT_
#define _DISABLE_SYSTEM_CUTSCENE_EVENT_

#include <string>

#include "cutscene_event.h"

namespace omniscia::core {
    struct CE_DisableSystemProp {
        CE_Prop _base;
    };
    
    template<class T>
    class CE_DisableSystemEvent : public CE_DisableSystemProp, public CE_Event {
        private:
            CE_DisableSystemEvent() {}
            CE_DisableSystemEvent(const CE_DisableSystemEvent&) {}
            void operator=(const CE_DisableSystemEvent&) {}

        public:
            CE_DisableSystemEvent(const auto& data = CE_DisableSystemProp{}) : CE_DisableSystemProp(data), CE_Event(*(CE_Prop*)&data) {
                
            }
            
            void execute() override {
                T::get_instance().disable();
            }
    };
}

#endif
