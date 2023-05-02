#ifndef _SHOW_DIALOGUE_TAB_CUTSCENE_EVENT_
#define _SHOW_DIALOGUE_TAB_CUTSCENE_EVENT_

#include <string>
#include <functional>

#include "cutscene_event.h"
#include "scene.h"
#include "camera.h"

namespace omniscia::core {
    struct CE_ShowDialogueTabProp {
        CE_Prop _base;
    };

    class CE_ShowDialogueTabEvent : public CE_ShowDialogueTabProp , public CE_Event {
        private:
            CE_ShowDialogueTabEvent();
            CE_ShowDialogueTabEvent(const CE_ShowDialogueTabEvent&);
            void operator=(const CE_ShowDialogueTabEvent&);

            void reset() override {
                reset_base();
            }

        public:
            CE_ShowDialogueTabEvent(const CE_ShowDialogueTabProp& data = CE_ShowDialogueTabProp{});
            
            void execute() override;
    };
}

#endif
