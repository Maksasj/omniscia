#ifndef _ECS_COMPONENT_INTERACTIVE_PRESS_H_
#define _ECS_COMPONENT_INTERACTIVE_PRESS_H_

#include <array>
#include <memory>
#include <iostream>
#include <functional>

#include "ecs/motion/ecs_acceleration.h"
#include "ecs/ecs_component.tpp"
#include "ecs/interactive/ecs_interactive.h"
#include "ecs/motion/ecs_trigger_aabb_collider.h"
#include "ecs/motion/ecs_velocity.h"
#include "timesystem.h"
#include "ecs/ecs_system.h"
#include "controls.h"
#include "ecs/entity.h"

namespace omniscia::core::ecs {
    using namespace omni::types;
    using namespace omniscia::core;

    class ECS_InteractivePress : public ECS_Interactive {
        public:
            friend class omni::reflector::FieldFriendlyScope;
            friend class omni::reflector::Reflection<ECS_InteractivePress>;

            ECS_InteractivePress(const f32& cooldown, const std::function<void(void)>& lambda);

            void update() override;

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_InteractivePress>(*this));
            }

            void _type_query(void* query) override {
                DebugFieldQuery::debug_component_edit_query<ECS_InteractivePress>(*this);
            }
    };
}

OMNI_ADAPT_STRUCTURE_NAME(omniscia::core::ecs, ECS_InteractivePress, _enabled, _cooldown, _timer);

#endif
