#ifndef _CAMERA_MOVE_EVENT_CUTSCENE_EVENT_
#define _CAMERA_MOVE_EVENT_CUTSCENE_EVENT_

#include <functional>
#include <string>

#include "camera.h"
#include "cutscene_event.h"

namespace omniscia::core {
    struct CE_CameraMoveProp {
        CE_Prop _base;

        Vec3f _startPosition = Vec3f{0.0f, 0.0f, 0.0f};
        Vec3f _finishPosition = Vec3f{0.0f, 0.0f, 0.0f};
        std::function<Vec3f(const Vec3f&, const Vec3f&, const f32&)> _shapingFunction;
    };

    class CE_CameraMoveEvent : public CE_CameraMoveProp , public CE_Event {
        private:
            CE_CameraMoveEvent();
            CE_CameraMoveEvent(const CE_CameraMoveEvent&);
            void operator=(const CE_CameraMoveEvent&);

            void reset() override {
                reset_base();
            }

        public:
            CE_CameraMoveEvent(const CE_CameraMoveProp& data = CE_CameraMoveProp{});
            
            void execute() override;
    };
}

#endif
