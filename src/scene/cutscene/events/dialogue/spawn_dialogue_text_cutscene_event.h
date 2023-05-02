#ifndef _SPAWN_DIALOGUE_TEXT_CUTSCENE_EVENT_
#define _SPAWN_DIALOGUE_TEXT_CUTSCENE_EVENT_

#include <string>
#include <functional>

#include "cutscene_event.h"
#include "scene.h"
#include "camera.h"

namespace omniscia::core {
    struct CE_SpawnDialogueTextProp {
        CE_Prop _base;

        std::string _entityTmpName = "";
    };

    class CE_SpawnDialogueTextEvent : public CE_SpawnDialogueTextProp , public CE_Event {
        private:
            CE_SpawnDialogueTextEvent();
            CE_SpawnDialogueTextEvent(const CE_SpawnDialogueTextEvent&);
            void operator=(const CE_SpawnDialogueTextEvent&);

            void reset() override {
                reset_base();
            }

        public:
            CE_SpawnDialogueTextEvent(const CE_SpawnDialogueTextProp& data = CE_SpawnDialogueTextProp{});
            
            void execute() override;
    };
}

#endif
