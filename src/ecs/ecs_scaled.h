#ifndef _ECS_COMPONENT_SCALED_H_
#define _ECS_COMPONENT_SCALED_H_

#include <array>
#include <memory>
#include <iostream>

#include "ecs_component.tpp"
#include "controls.h"
#include "entity.h"

namespace omniscia::core::ecs {
    class ECS_Scaled : public ECS_Component {
        private:
            Vec2f _scale;
        public:
            void reindex(void* parent) override;

            ECS_Scaled(const f32& scaleX = 0.0f, const f32& scaleY = 0.0f);
            ECS_Scaled(const Vec2f& scale);
            
            Vec2f get_scale() const;
            void set_scale(const Vec2f& newScale);

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_Scaled>(*this));
            }
    };
}

#endif