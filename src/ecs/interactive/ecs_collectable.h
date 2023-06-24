#ifndef _ECS_COMPONENT_COLLECTABLE_H_
#define _ECS_COMPONENT_COLLECTABLE_H_

#include <array>
#include <memory>
#include <iostream>
#include <functional>

#include "ecs_acceleration.h"
#include "ecs_component.tpp"
#include "ecs_interactive.h"
#include "ecs_trigger_aabb_collider.h"
#include "ecs_popup_renderer.h"
#include "ecs_velocity.h"
#include "timesystem.h"
#include "ecs_system.h"
#include "controls.h"
#include "entity.h"
#include "debug_info.h"

namespace omniscia::core::ecs {
    using namespace omni::types;
    using namespace omniscia::core;

    class ECS_Collectable : public ECS_Interactive {        
        public:
            friend class omni::reflector::FieldFriendlyScope;
            friend class omni::reflector::Reflection<ECS_Collectable>;

            void time_sync() override;
            void reindex(void* parent) override;

            ECS_Collectable();

            void update() override;

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_Collectable>(*this));
            }

            void _type_query(void* query) override {
                DebugFieldQuery::debug_component_edit_query<ECS_Collectable>(*this);
            }
    };
}

OMNI_ADAPT_STRUCTURE_NAME(omniscia::core::ecs, ECS_Collectable, _enabled, _cooldown, _timer);

#endif
