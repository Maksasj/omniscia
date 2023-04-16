#ifndef _CAMERA_ZOME_EVENT_CUTSCENE_EVENT_
#define _CAMERA_ZOME_EVENT_CUTSCENE_EVENT_

#include <functional>
#include <string>

#include "camera.h"
#include "cutscene_event.h"

namespace omniscia::core {
    struct CE_CameraZoomProp {
        CE_Prop _base;

        f32 _startZoom = 1.0f;
        f32 _finishZoom = 1.0f;
        std::function<f32(const f32&, const f32&, const f32&)> _shapingFunction;
    };

    class CE_CameraZoomEvent : public CE_CameraZoomProp , public CE_Event {
        private:
            CE_CameraZoomEvent() {}
            CE_CameraZoomEvent(const CE_CameraZoomEvent&) {}
            void operator=(const CE_CameraZoomEvent&) {}

        public:
            CE_CameraZoomEvent(const auto& data = CE_CameraZoomProp{}) : CE_CameraZoomProp(data), CE_Event(*(CE_Prop*)&data) {

            }
            
            void execute() override {
                const f32 t = this->get_current_duration() / _durationTime;

                auto newPos = _shapingFunction(_startZoom, _finishZoom, t);
                Camera::get_instance().set_zoom(newPos);
            }
    };
}

#endif
