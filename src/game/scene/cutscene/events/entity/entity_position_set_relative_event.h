#ifndef _ENTITY_POSITION_SET_RELATIVE_EVENT_CUTSCENE_EVENT_
#define _ENTITY_POSITION_SET_RELATIVE_EVENT_CUTSCENE_EVENT_

#include <functional>
#include <string>

#include "camera.h"
#include "cutscene_event.h"

namespace omniscia::core {
    using namespace omni::types;
    
    struct CE_EntityPositionSetRelativeProp {
        CE_Prop _base;

        std::string _entityTmpName = "";
        Vec2f _relativePosition = Vec2f{0.0f, 0.0f};
    };

    class CE_EntityPositionSetRelativeEvent : public CE_EntityPositionSetRelativeProp , public CE_Event {
        private:
            CE_EntityPositionSetRelativeEvent();
            CE_EntityPositionSetRelativeEvent(const CE_EntityPositionSetRelativeEvent&);
            void operator=(const CE_EntityPositionSetRelativeEvent&);

            void reset() override {
                reset_base();
            }

        public:
            CE_EntityPositionSetRelativeEvent(const CE_EntityPositionSetRelativeProp& data = CE_EntityPositionSetRelativeProp{});
            
            void execute() override;
    };
}

#endif
