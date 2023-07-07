#ifndef _TERMINAL_PRINT_CUTSCENE_EVENT_
#define _TERMINAL_PRINT_CUTSCENE_EVENT_

#include <string>

#include "scene/cutscene/cutscene_event.h"

namespace omniscia::core {
    using namespace omni::types;
    
    struct CE_LogProp {
        CE_Prop _base;
        std::string _message = "";
    };

    class CE_LogEvent : public CE_LogProp , public CE_Event {
        private:
            CE_LogEvent();
            CE_LogEvent(const CE_LogEvent&);
            void operator=(const CE_LogEvent&);

        public:
            CE_LogEvent(const CE_LogProp& data = CE_LogProp{});
            
            void reset() override {
                reset_base();
            }

            void execute() override;
    };
}

#endif
