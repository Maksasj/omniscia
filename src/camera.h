#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "types.tpp"

namespace omniscia::core {
    using namespace omni::types;
    
    class Camera {
        private:
            Camera() {
                _pos = Vec3f{0.0f, 0.0f, 0.0f};
                _zoom = 1.0f;
            }
            
            Camera(const Camera&) {}
            void operator=(Camera const&) {};

            Vec3f _pos;
            f32 _zoom;
        public:
            Vec3f get_pos() const {
                return _pos;
            }

            void set_pos(const Vec3f& newPos) {
                _pos = newPos;
            }

            Vec3f& ref_pos() {
                return _pos;
            }

            f32 get_zoom() const {
                return _zoom;
            }

            void set_zoom(const f32& newZoom) {
                _zoom = newZoom;
            }

            static Camera& get_instance() {
                static Camera instance;
                return instance;
            }
    };
}

#endif
