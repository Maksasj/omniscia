#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "types.tpp"

namespace omniscia::core {
    class Camera {
        private:
            Camera() {
                _pos = Vec3f{0.0f, 0.0f, 0.0f};
            }
            
            Camera(const Camera&) {}
            void operator=(Camera const&) {};

            Vec3f _pos;
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

            static Camera& get_instance() {
                static Camera instance;
                return instance;
            }
    };
}

#endif
