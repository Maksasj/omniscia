#ifndef _REDUCE_TIMELINE_FRAMES_CUTSCENE_EVENT_
#define _REDUCE_TIMELINE_FRAMES_CUTSCENE_EVENT_

#include <string>

#include "cutscene_event.h"

namespace omniscia::core {
    using namespace omni::types;
    
    struct CE_ReduceTimelineFramesProp {
        CE_Prop _base;
    };

    class CE_ReduceTimelineFramesEvent : public CE_ReduceTimelineFramesProp , public CE_Event {
        private:
            CE_ReduceTimelineFramesEvent();
            CE_ReduceTimelineFramesEvent(const CE_ReduceTimelineFramesEvent&);
            void operator=(const CE_ReduceTimelineFramesEvent&);

            void reset() override {
                reset_base();
            }

        public:
            CE_ReduceTimelineFramesEvent(const CE_ReduceTimelineFramesProp& data = CE_ReduceTimelineFramesProp{});
            void execute() override;
    };
}

#endif
