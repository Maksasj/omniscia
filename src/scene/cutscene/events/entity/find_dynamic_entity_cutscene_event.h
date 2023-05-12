#ifndef _FIND_DYNAMIC_ENTITY_CUTSCENE_EVENT_
#define _FIND_DYNAMIC_ENTITY_CUTSCENE_EVENT_

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
    class CE_FindDynamicEntityEvent : public CE_IndexDynamicEntityProp , public CE_Event {
        private:
            CE_FindDynamicEntityEvent();
            CE_FindDynamicEntityEvent(const CE_FindDynamicEntityEvent&);
            void operator=(const CE_FindDynamicEntityEvent&);

            void reset() override {
                reset_base();
            }

        public:
            CE_FindDynamicEntityEvent(const CE_IndexDynamicEntityProp& data = CE_IndexDynamicEntityProp{});
            
            void execute() override;
    };
}

#endif
