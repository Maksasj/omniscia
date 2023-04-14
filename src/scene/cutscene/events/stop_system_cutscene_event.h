#ifndef _STOP_SYSTEM_CUTSCENE_EVENT_
#define _STOP_SYSTEM_CUTSCENE_EVENT_

#include <string>

#include "cutscene_event.h"

namespace omniscia::core {
    struct CE_StopSystemProp {
        CE_Prop _base;
    };
    
    template<class T>
    class CE_StopSystemEvent : public CE_StopSystemProp, public CE_Event {
        private:
            CE_StopSystemEvent() {}
            CE_StopSystemEvent(const CE_StopSystemEvent&) {}
            void operator=(const CE_StopSystemEvent&) {}

        public:
            CE_StopSystemEvent(const auto& data = CE_StopSystemProp{}) : CE_StopSystemProp(data), CE_Event(*(CE_Prop*)&data) {
                
            }
            
            void execute() override {
                T::get_instance().disable();
            }
    };
}

#endif
