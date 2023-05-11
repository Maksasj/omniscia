#ifndef _WAIT_CUTSCENE_CUTSCENE_EVENT_
#define _WAIT_CUTSCENE_CUTSCENE_EVENT_

#include <string>
#include <functional>

#include "cutscene_event.h"

namespace omniscia::core {
    using namespace omni::types;
    
    struct CE_WaitCutsceneProp {
        CE_Prop _base;

        const std::function<bool(void)> _lambda = []() { return true; };
    };

    class CE_WaitCutsceneEvent : public CE_WaitCutsceneProp , public CE_Event {
        private:
            CE_WaitCutsceneEvent();
            CE_WaitCutsceneEvent(const CE_WaitCutsceneEvent&);
            void operator=(const CE_WaitCutsceneEvent&);

            void reset() override {
                reset_base();
            }

        public:
            CE_WaitCutsceneEvent(const CE_WaitCutsceneProp& data = CE_WaitCutsceneProp{});
            void execute() override;
    };
}

#endif
