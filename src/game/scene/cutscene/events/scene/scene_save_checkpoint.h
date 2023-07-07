#ifndef _SCENE_SAVE_CHECKPOINT_CUTSCENE_EVENT_
#define _SCENE_SAVE_CHECKPOINT_CUTSCENE_EVENT_

#include <string>

#include "scene/cutscene/cutscene_event.h"

namespace omniscia::core {
    using namespace omni::types;
    
    struct CE_SceneSaveCheckpointProp {
        CE_Prop _base;
    };

    class CE_SceneSaveCheckpointEvent : public CE_SceneSaveCheckpointProp , public CE_Event {
        private:
            CE_SceneSaveCheckpointEvent();
            CE_SceneSaveCheckpointEvent(const CE_SceneSaveCheckpointEvent&);
            void operator=(const CE_SceneSaveCheckpointEvent&);

            void reset() override {
                reset_base();
            }

        public:
            CE_SceneSaveCheckpointEvent(const CE_SceneSaveCheckpointProp& data = CE_SceneSaveCheckpointProp{});
            void execute() override;
    };
}

#endif
