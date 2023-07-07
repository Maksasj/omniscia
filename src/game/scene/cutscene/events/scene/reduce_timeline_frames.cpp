#include "reduce_timeline_frames.h"
#include "game.h"

omniscia::core::CE_ReduceTimelineFramesEvent::CE_ReduceTimelineFramesEvent() {

}

omniscia::core::CE_ReduceTimelineFramesEvent::CE_ReduceTimelineFramesEvent(const CE_ReduceTimelineFramesEvent&) {

}

void omniscia::core::CE_ReduceTimelineFramesEvent::operator=(const CE_ReduceTimelineFramesEvent&) {

}

omniscia::core::CE_ReduceTimelineFramesEvent::CE_ReduceTimelineFramesEvent(const CE_ReduceTimelineFramesProp& data) : CE_ReduceTimelineFramesProp(data), CE_Event(*(CE_Prop*)&data) {

}

void omniscia::core::CE_ReduceTimelineFramesEvent::execute() {
    auto& timeLine = Game::get_instance().ref_time_line();

    timeLine.reduce_actual_frame();
}
