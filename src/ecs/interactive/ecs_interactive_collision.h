#ifndef _ECS_COMPONENT_INTERACTIVE_COLLISION_H_
#define _ECS_COMPONENT_INTERACTIVE_COLLISION_H_

#include <array>
#include <memory>
#include <iostream>
#include <functional>

#include "ecs_acceleration.h"
#include "ecs_component.tpp"
#include "ecs_interactive.h"
#include "ecs_trigger_aabb_collider.h"
#include "ecs_velocity.h"
#include "timesystem.h"
#include "ecs_system.h"
#include "controls.h"
#include "entity.h"

namespace omniscia::core::ecs {
    using namespace omni::types;
    using namespace omniscia::core;

    class ECS_InteractiveCollision : public ECS_Interactive {
        public:
            ECS_InteractiveCollision(const f32& cooldown, const std::function<void(void)>& lambda);

            void update() override;

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_InteractiveCollision>(*this));
            }

            u64 byte_size() override {
                return sizeof(ECS_InteractiveCollision);
            }
    };
}

#endif
