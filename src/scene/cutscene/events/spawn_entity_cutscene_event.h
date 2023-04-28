#ifndef _SPAWN_ENTITY_CUTSCENE_EVENT_
#define _SPAWN_ENTITY_CUTSCENE_EVENT_

#include <string>
#include <functional>

#include "cutscene_event.h"
#include "scene.h"

namespace omniscia::core {
    struct CE_SpawnEntityProp {
        CE_Prop _base;

        std::function<void(Scene*)> _summonLambda = [](Scene*) {};
    };

    class CE_SpawnEntityEvent : public CE_SpawnEntityProp , public CE_Event {
        private:
            CE_SpawnEntityEvent();
            CE_SpawnEntityEvent(const CE_SpawnEntityEvent&);
            void operator=(const CE_SpawnEntityEvent&);

        public:
            CE_SpawnEntityEvent(const CE_SpawnEntityProp& data = CE_SpawnEntityProp{});
            
            void execute() override;
    };
}

#endif
