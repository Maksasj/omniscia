#ifndef _ECS_COMPONENT_FRICTION_H_
#define _ECS_COMPONENT_FRICTION_H_

#include <array>
#include <memory>
#include <iostream>

#include "types.tpp"
#include "ecs_component.tpp"
#include "entity.h"
#include "controls.h"

namespace omniscia::core::ecs {
    class ECS_Friction : public ECS_Component {
        private:
            f32 _friction;
        public:
            ECS_Friction();
            ECS_Friction(const f32& vel);

            void reindex(void* parent) override;

            f32 get_friction() const;
            void set_friction(const f32& friction);

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_Friction>(*this));
            }
    };
}

#endif