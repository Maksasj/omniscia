#ifndef _ECS_COMPONENT_POSITIONED_H_
#define _ECS_COMPONENT_POSITIONED_H_

#include <array>
#include <memory>
#include <iostream>

#include "ecs_component.tpp"
#include "entity.h"
#include "controls.h"

namespace omniscia::core::ecs {
    class ECS_Positioned : public ECS_Component {
        private:
            Vec3f _pos;
        public:
            ECS_Positioned();
            ECS_Positioned(const Vec3f& pos);

            void reindex(void* parent) override;

            Vec3f get_pos() const;
            void set_pos(const Vec3f& newPos);
            void move_pos(const Vec3f& movedPos);

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_Positioned>(*this));
            }
    };
}

#endif