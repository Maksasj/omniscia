#ifndef _DESTROY_ENTITY_CUTSCENE_EVENT_
#define _DESTROY_ENTITY_CUTSCENE_EVENT_

#include <functional>
#include <string>

#include "camera.h"
#include "cutscene_event.h"

namespace omniscia::core {
    using namespace omni::types;
    
    struct CE_DestroyEntityProp {
        CE_Prop _base;

        std::string _entityTmpName = "";
    };

    class CE_DestroyEntityEvent : public CE_DestroyEntityProp , public CE_Event {
        private:
            CE_DestroyEntityEvent();
            CE_DestroyEntityEvent(const CE_DestroyEntityEvent&);
            void operator=(const CE_DestroyEntityEvent&);

            void reset() override {
                reset_base();
            }

        public:
            CE_DestroyEntityEvent(const CE_DestroyEntityProp& data = CE_DestroyEntityProp{});
            
            void execute() override;
    };
}

#endif
