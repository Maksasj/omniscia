#include "camera_move_event.h"

omniscia::core::CE_CameraMoveEvent::CE_CameraMoveEvent() {

}

omniscia::core::CE_CameraMoveEvent::CE_CameraMoveEvent(const CE_CameraMoveEvent&) {

}

void omniscia::core::CE_CameraMoveEvent::operator=(const CE_CameraMoveEvent&) {

}

omniscia::core::CE_CameraMoveEvent::CE_CameraMoveEvent(const CE_CameraMoveProp& data) : CE_CameraMoveProp(data), CE_Event(*(CE_Prop*)&data) {

}

void omniscia::core::CE_CameraMoveEvent::execute() {
    const f32 t = this->get_current_duration() / _durationTime;

    auto newPos = _shapingFunction(_startPosition, _finishPosition, t);
    Camera::get_instance().set_pos(newPos);
}
