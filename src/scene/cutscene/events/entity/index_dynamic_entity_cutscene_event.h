#ifndef _INDEX_DYNAMIC_ENTITY_CUTSCENE_EVENT_
#define _INDEX_DYNAMIC_ENTITY_CUTSCENE_EVENT_

#include <functional>
#include <string>

#include "camera.h"
#include "cutscene_event.h"

namespace omniscia::core {
    using namespace omni::types;
    
    struct CE_IndexDynamicEntityProp {
        CE_Prop _base;

        std::string _entityTmpName = "";
    };

    template<class _T>
    class CE_IndexDynamicEntityEvent : public CE_IndexDynamicEntityProp , public CE_Event {
        private:
            CE_IndexDynamicEntityEvent();
            CE_IndexDynamicEntityEvent(const CE_IndexDynamicEntityEvent&);
            void operator=(const CE_IndexDynamicEntityEvent&);

            void reset() override {
                reset_base();
            }

        public:
            CE_IndexDynamicEntityEvent(const CE_IndexDynamicEntityProp& data = CE_IndexDynamicEntityProp{});
            
            void execute() override;
    };
}

#endif
