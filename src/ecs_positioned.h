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

            ECS_Positioned(const Entity& entity) {
                _pos = Vec3f{0.0f, 0.0f, 0.0f};
            }

            void reindex(void* parent) override {}

            Vec3f get_pos() const {
                return _pos;
            }

            void set_pos(const Vec3f& newPos) {
                _pos = newPos;
            }
            
            void move_pos(const Vec3f& movedPos) {
                _pos += movedPos;
            }

            std::shared_ptr<ECS_Component> clone() override {
                //std::cout << "Yes i guess ?\n";
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_Positioned>(*this));
            }
    };
}

#endif