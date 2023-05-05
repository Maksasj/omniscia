#ifndef _SCENE_LOAD_CHECKPOINT_CUTSCENE_EVENT_
#define _SCENE_LOAD_CHECKPOINT_CUTSCENE_EVENT_

#include <string>

#include "cutscene_event.h"

namespace omniscia::core {
    using namespace omni::types;
    
    struct CE_SceneLoadCheckpointProp {
        CE_Prop _base;
    };

    class CE_SceneLoadCheckpointEvent : public CE_SceneLoadCheckpointProp , public CE_Event {
        private:
            CE_SceneLoadCheckpointEvent();
            CE_SceneLoadCheckpointEvent(const CE_SceneLoadCheckpointEvent&);
            void operator=(const CE_SceneLoadCheckpointEvent&);

            void reset() override {
                reset_base();
            }

        public:
            CE_SceneLoadCheckpointEvent(const CE_SceneLoadCheckpointProp& data = CE_SceneLoadCheckpointProp{});
            void execute() override;
    };
}

#endif
