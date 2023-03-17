#ifndef _ECS_COMPONENT_SCALED_H_
#define _ECS_COMPONENT_SCALED_H_

#include <array>
#include <memory>
#include <iostream>

#include "ecs_component.tpp"
#include "controls.h"

namespace omniscia::core::ecs {
    class ECS_Scaled : public ECS_Component {
        private:
            Vec2f _scale;
        public:
            ECS_Scaled() { _scale = Vec2f{1.0f, 1.0f}; }
            ECS_Scaled(const Entity& entity) { _scale = Vec2f{1.0f, 1.0f}; }
            ECS_Scaled(const Vec2f& scale) { _scale = scale; }
            ECS_Scaled(const Vec2f& scale, const Entity& entity) { _scale = scale; }

            void reindex(void* parent) override {}

            Vec2f get_scale() const {
                return _scale;
            }

            void set_scale(const Vec2f& newScale) {
                _scale = newScale;
            }

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_Scaled>(*this));
            }
    };
}

#endif