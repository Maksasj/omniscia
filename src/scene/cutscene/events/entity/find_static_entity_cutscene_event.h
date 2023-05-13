#ifndef _FIND_STATIC_ENTITY_CUTSCENE_EVENT_
#define _FIND_STATIC_ENTITY_CUTSCENE_EVENT_

#include <functional>
#include <string>

#include "camera.h"
#include "cutscene_event.h"

namespace omniscia::core {
    using namespace omni::types;
    
    struct CE_FindStaticEntityProp {
        CE_Prop _base;

        std::string _entityTmpName = "";
    };

    template<class _T>
    class CE_FindStaticEntityEvent : public CE_FindStaticEntityProp , public CE_Event {
        private:
            CE_FindStaticEntityEvent();
            CE_FindStaticEntityEvent(const CE_FindStaticEntityEvent&);
            void operator=(const CE_FindStaticEntityEvent&);

            void reset() override {
                reset_base();
            }

        public:
            CE_FindStaticEntityEvent(const CE_FindStaticEntityProp& data = CE_FindStaticEntityProp{});
            
            void execute() override;
    };
}

#endif
