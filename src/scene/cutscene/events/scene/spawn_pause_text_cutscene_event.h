#ifndef _SPAWN_PAUSE_TEXT_CUTSCENE_EVENT_
#define _SPAWN_PAUSE_TEXT_CUTSCENE_EVENT_

#include <string>
#include <functional>

#include "cutscene_event.h"
#include "scene.h"
#include "camera.h"

namespace omniscia::core {
    using namespace omni::types;
    
    struct CE_SpawnPauseTextProp {
        CE_Prop _base;
        
        std::string _entityTmpName = "";
    };

    class CE_SpawnPauseTextEvent : public CE_SpawnPauseTextProp , public CE_Event {
        private:
            CE_SpawnPauseTextEvent();
            CE_SpawnPauseTextEvent(const CE_SpawnPauseTextEvent&);
            void operator=(const CE_SpawnPauseTextEvent&);

            void reset() override {
                reset_base();
            }
            
        public:
            CE_SpawnPauseTextEvent(const CE_SpawnPauseTextProp& data = CE_SpawnPauseTextProp{});
            
            void execute() override;
    };
}

#endif
