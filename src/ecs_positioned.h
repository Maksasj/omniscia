#ifndef _ECS_COMPONENT_POSITIONED_H_
#define _ECS_COMPONENT_POSITIONED_H_

#include <array>
#include <memory>
#include <iostream>

#include "ecs_component.tpp"
#include "controls.h"

namespace omniscia::core::ecs {
    class ECS_Positioned : public ECS_Component {
        private:
            Vec3f _pos;
        public:
            ECS_Positioned() {
                _pos = Vec3f{0.0f, 0.0f, 0.0f};
            }

            Vec3f get_pos() const {
                return _pos;
            }

            void set_pos(const Vec3f& newPos) {
                _pos = newPos;
            }
    };
}

#endif