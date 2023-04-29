#include "camera_zoom_event.h"

omniscia::core::CE_CameraZoomEvent::CE_CameraZoomEvent() {

}

omniscia::core::CE_CameraZoomEvent::CE_CameraZoomEvent(const CE_CameraZoomEvent&) {

}

void omniscia::core::CE_CameraZoomEvent::operator=(const CE_CameraZoomEvent&) {

}

omniscia::core::CE_CameraZoomEvent::CE_CameraZoomEvent(const CE_CameraZoomProp& data) : CE_CameraZoomProp(data), CE_Event(*(CE_Prop*)&data) {

}

void omniscia::core::CE_CameraZoomEvent::execute() {
    const f32 t = this->get_current_duration() / _durationTime;

    auto newZoom = _shapingFunction(_startZoom, _finishZoom, t);
    Camera::get_instance().set_zoom(newZoom);
}
