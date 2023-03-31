#ifndef _ECS_COMPONENT_FRICTION_H_
#define _ECS_COMPONENT_FRICTION_H_

#include <array>
#include <memory>
#include <iostream>

#include "ecs_component.tpp"
#include "controls.h"
#include "types.tpp"
#include "entity.h"

namespace omniscia::core::ecs {
    class ECS_Friction : public ECS_Component {
        private:
            f32 _friction;
        public:
            void reindex(void* parent) override;

            ECS_Friction(const f32& friction = -0.01f);

            f32 get_friction() const;
            f32& ref_friction();
            
            void set_friction(const f32& friction);

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_Friction>(*this));
            }
    };
}

#endif