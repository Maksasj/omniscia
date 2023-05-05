#ifndef _CAMERA_ZOME_EVENT_CUTSCENE_EVENT_
#define _CAMERA_ZOME_EVENT_CUTSCENE_EVENT_

#include <functional>
#include <string>

#include "camera.h"
#include "cutscene_event.h"

namespace omniscia::core {
    using namespace omni::types;
    
    struct CE_CameraZoomProp {
        CE_Prop _base;

        f32 _startZoom = 1.0f;
        f32 _finishZoom = 1.0f;
        std::function<f32(const f32&, const f32&, const f32&)> _shapingFunction;
    };

    class CE_CameraZoomEvent : public CE_CameraZoomProp , public CE_Event {
        private:
            CE_CameraZoomEvent();
            CE_CameraZoomEvent(const CE_CameraZoomEvent&);
            void operator=(const CE_CameraZoomEvent&);

            void reset() override {
                reset_base();
            }

        public:
            CE_CameraZoomEvent(const CE_CameraZoomProp& data = CE_CameraZoomProp{});
            
            void execute() override;
    };
}

#endif
