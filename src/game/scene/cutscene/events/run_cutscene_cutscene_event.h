#ifndef _RUN_CUTSCENE_CUTSCENE_EVENT_
#define _RUN_CUTSCENE_CUTSCENE_EVENT_

#include <string>

#include "cutscene_event.h"

namespace omniscia::core {
    using namespace omni::types;
    
    struct CE_RunCutsceneCutsceneProp {
        CE_Prop _base;
        std::string _cutsceneId;
    };

    class CE_RunCutsceneCutsceneEvent : public CE_RunCutsceneCutsceneProp , public CE_Event {
        private:
            CE_RunCutsceneCutsceneEvent();
            CE_RunCutsceneCutsceneEvent(const CE_RunCutsceneCutsceneEvent&);
            void operator=(const CE_RunCutsceneCutsceneEvent&);

            void reset() override {
                reset_base();
            }

        public:
            CE_RunCutsceneCutsceneEvent(const CE_RunCutsceneCutsceneProp& data = CE_RunCutsceneCutsceneProp{});
            void execute() override;
    };
}

#endif
