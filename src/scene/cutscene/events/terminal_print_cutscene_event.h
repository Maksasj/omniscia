#ifndef _TERMINAL_PRINT_CUTSCENE_EVENT_
#define _TERMINAL_PRINT_CUTSCENE_EVENT_

#include <string>

#include "cutscene_event.h"

namespace omniscia::core {
    struct CE_LogProp {
        CE_Prop _base;
        std::string _message = "";
    };

    class CE_LogEvent : public CE_LogProp , public CE_Event {
        private:
            CE_LogEvent() {}
            CE_LogEvent(const CE_LogEvent&) {}
            void operator=(const CE_LogEvent&) {}

        public:
            CE_LogEvent(const auto& data = CE_LogProp{}) : CE_LogProp(data), CE_Event(*(CE_Prop*)&data) {

            }
            
            void execute() override {
                std::cout << _message << "\n";
            }
    };
}

#endif
