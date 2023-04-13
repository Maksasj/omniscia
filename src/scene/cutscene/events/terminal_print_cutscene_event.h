#ifndef _TERMINAL_PRINT_CUTSCENE_EVENT_
#define _TERMINAL_PRINT_CUTSCENE_EVENT_

#include <string>

#include "cutscene_event.h"

namespace omniscia::core {
    struct CE_LogProp {
        CE_Prop _base;
        std::string _message = "";
    };

    struct CE_LogEvent : public CE_LogProp , public CE_Event {
        CE_LogEvent(const CE_LogProp& data = CE_LogProp{}) : CE_LogProp(data) {
            
        }
        
        void run() override {
            std::cout << _message << "\n";
        }
    };
}

#endif
