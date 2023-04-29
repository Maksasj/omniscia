#ifndef _ENTITY_POSITION_SET_EVENT_CUTSCENE_EVENT_
#define _ENTITY_POSITION_SET_EVENT_CUTSCENE_EVENT_

#include <functional>
#include <string>

#include "camera.h"
#include "cutscene_event.h"

namespace omniscia::core {
    struct CE_EntityPositionSetProp {
        CE_Prop _base;

        std::string _entityTmpName = "";
        Vec2f _newPosition = Vec2f{0.0f, 0.0f};
    };

    class CE_EntityPositionSetEvent : public CE_EntityPositionSetProp , public CE_Event {
        private:
            CE_EntityPositionSetEvent();
            CE_EntityPositionSetEvent(const CE_EntityPositionSetEvent&);
            void operator=(const CE_EntityPositionSetEvent&);

        public:
            CE_EntityPositionSetEvent(const CE_EntityPositionSetProp& data = CE_EntityPositionSetProp{});
            
            void execute() override;
    };
}

#endif
