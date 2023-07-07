#ifndef _SPAWN_DIALOGUE_TAB_CUTSCENE_EVENT_
#define _SPAWN_DIALOGUE_TAB_CUTSCENE_EVENT_

#include <string>
#include <functional>

#include "scene/cutscene/cutscene_event.h"
#include "scene/scene.h"
#include "camera.h"

namespace omniscia::core {
    using namespace omni::types;
    
    struct CE_SpawnDialogueTabProp {
        CE_Prop _base;

        std::string _entityTmpName = "";
    };

    class CE_SpawnDialogueTabEvent : public CE_SpawnDialogueTabProp , public CE_Event {
        private:
            CE_SpawnDialogueTabEvent();
            CE_SpawnDialogueTabEvent(const CE_SpawnDialogueTabEvent&);
            void operator=(const CE_SpawnDialogueTabEvent&);

            void reset() override {
                reset_base();
            }

        public:
            CE_SpawnDialogueTabEvent(const CE_SpawnDialogueTabProp& data = CE_SpawnDialogueTabProp{});
            
            void execute() override;
    };
}

#endif
