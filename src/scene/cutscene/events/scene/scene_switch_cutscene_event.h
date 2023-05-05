#ifndef _SCENE_SWITCH_CUTSCENE_EVENT_
#define _SCENE_SWITCH_CUTSCENE_EVENT_

#include <string>

#include "cutscene_event.h"

namespace omniscia::core {
    using namespace omni::types;
    
    struct CE_SceneSwitchProp {
        CE_Prop _base;
        std::string _sceneName = "";
    };

    class CE_SceneSwitchEvent : public CE_SceneSwitchProp , public CE_Event {
        private:
            CE_SceneSwitchEvent();
            CE_SceneSwitchEvent(const CE_SceneSwitchEvent&);
            void operator=(const CE_SceneSwitchEvent&);

            void reset() override {
                reset_base();
            }

        public:
            CE_SceneSwitchEvent(const CE_SceneSwitchProp& data = CE_SceneSwitchProp{});
            void execute() override;
    };
}

#endif
