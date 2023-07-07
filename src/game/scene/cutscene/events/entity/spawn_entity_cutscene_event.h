#ifndef _SPAWN_ENTITY_CUTSCENE_EVENT_
#define _SPAWN_ENTITY_CUTSCENE_EVENT_

#include <string>
#include <functional>

#include "scene/cutscene/cutscene_event.h"
#include "scene/scene.h"

namespace omniscia::core {
    using namespace omni::types;
    
    struct CE_SpawnEntityProp {
        CE_Prop _base;

        std::function<void(Scene*)> _summonLambda = [](Scene*) {};
    };

    class CE_SpawnEntityEvent : public CE_SpawnEntityProp , public CE_Event {
        private:
            CE_SpawnEntityEvent();
            CE_SpawnEntityEvent(const CE_SpawnEntityEvent&);
            void operator=(const CE_SpawnEntityEvent&);

            void reset() override {
                reset_base();
            }

        public:
            CE_SpawnEntityEvent(const CE_SpawnEntityProp& data = CE_SpawnEntityProp{});
            
            void execute() override;
    };
}

#endif
