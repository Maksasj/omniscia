#ifndef _ENTITY_POSITION_MOVE_EVENT_CUTSCENE_EVENT_
#define _ENTITY_POSITION_MOVE_EVENT_CUTSCENE_EVENT_

#include <functional>
#include <string>

#include "camera.h"
#include "cutscene_event.h"

namespace omniscia::core {
    struct CE_EntityPositionMoveProp {
        CE_Prop _base;

        std::string _entityTmpName = "";
        Vec2f _startPosition = Vec2f{0.0f, 0.0f};
        Vec2f _finishPosition = Vec2f{0.0f, 0.0f};
        std::function<Vec2f(const Vec2f&, const Vec2f&, const f32&)> _shapingFunction;
    };

    class CE_EntityPositionMoveEvent : public CE_EntityPositionMoveProp , public CE_Event {
        private:
            CE_EntityPositionMoveEvent();
            CE_EntityPositionMoveEvent(const CE_EntityPositionMoveEvent&);
            void operator=(const CE_EntityPositionMoveEvent&);

            void reset() override {
                reset_base();
            }

        public:
            CE_EntityPositionMoveEvent(const CE_EntityPositionMoveProp& data = CE_EntityPositionMoveProp{});
            
            void execute() override;
    };
}

#endif
