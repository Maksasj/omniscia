#ifndef _ENABLE_SYSTEM_CUTSCENE_EVENT_
#define _ENABLE_SYSTEM_CUTSCENE_EVENT_

#include <string>

#include "cutscene_event.h"

namespace omniscia::core {
    struct CE_EnableSystemProp {
        CE_Prop _base;
    };
    
    template<class T>
    class CE_EnableSystemEvent : public CE_EnableSystemProp, public CE_Event {
        private:
            CE_EnableSystemEvent() {}
            CE_EnableSystemEvent(const CE_EnableSystemEvent&) {}
            void operator=(const CE_EnableSystemEvent&) {}

        public:
            CE_EnableSystemEvent(const auto& data = CE_EnableSystemProp{}) : CE_EnableSystemProp(data), CE_Event(*(CE_Prop*)&data) {
                
            }
            
            void execute() override {
                T::get_instance().enable();
            }
    };
}

#endif
