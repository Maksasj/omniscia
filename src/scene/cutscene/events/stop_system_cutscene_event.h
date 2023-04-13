#ifndef _STOP_SYSTEM_CUTSCENE_EVENT_
#define _STOP_SYSTEM_CUTSCENE_EVENT_

#include <string>

#include "cutscene_event.h"

namespace omniscia::core {
    struct CE_StopSystemProp {
        CE_Prop _base;
    };
    
    template<class T>
    struct CE_StopSystemEvent : public CE_StopSystemProp, public CE_Event {
        CE_StopSystemEvent(const CE_StopSystemProp& data = CE_StopSystemProp{}) : CE_StopSystemProp(data) {
            
        }
        
        void run() override {
            T::get_instance().disable();
        }
    };
}

#endif
