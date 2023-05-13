#ifndef _ENTITY_COLLECT_EVENT_CUTSCENE_EVENT_
#define _ENTITY_COLLECT_EVENT_CUTSCENE_EVENT_

#include <functional>
#include <string>

#include "camera.h"
#include "cutscene_event.h"

namespace omniscia::core {
    using namespace omni::types;
    
    struct CE_EntityCollectProp {
        CE_Prop _base;

        std::string _entityTmpName = "";
        i32 _amount = 1;
    };

    class CE_EntityCollectEvent : public CE_EntityCollectProp , public CE_Event {
        private:
            CE_EntityCollectEvent();
            CE_EntityCollectEvent(const CE_EntityCollectEvent&);
            void operator=(const CE_EntityCollectEvent&);

            void reset() override {
                reset_base();
            }

        public:
            CE_EntityCollectEvent(const CE_EntityCollectProp& data = CE_EntityCollectProp{});
            
            void execute() override;
    };
}

#endif
