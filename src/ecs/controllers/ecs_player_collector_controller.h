#ifndef _ECS_COMPONENT_PLAYER_STAR_CONTROLLER_H_
#define _ECS_COMPONENT_PLAYER_STAR_CONTROLLER_H_

#include "ecs_state_machine_base.h"
#include "ecs_acceleration.h"
#include "ecs_sprite_flip.h"
#include "ecs_sprite_animation.h"
#include "ecs_movable_aabb_collider.h"
#include "ecs_sound_emitter.h"
#include "ecs_velocity.h"

#include "debug_info.h"

namespace omniscia::core::ecs {
    using namespace omni::types;
    using namespace omniscia::core;

    class ECS_PlayerCollectorController : public ECS_StateMachineBase {
        private:
            i32 _collected;

        public:
            friend class omni::reflector::FieldFriendlyScope;
            friend class omni::reflector::Reflection<ECS_PlayerCollectorController>;

            void time_sync() override;
            void reindex(void* parent) override;

            ECS_PlayerCollectorController();

            ECS_PlayerCollectorController(ECS_PlayerCollectorController const& comp);

            void player_collector_state();
            void collect();

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_PlayerCollectorController>(*this));
            }

            void _type_query(void* query) override {
                DebugFieldQuery::debug_component_edit_query<ECS_PlayerCollectorController>(*this);
            }
    };
}

OMNI_ADAPT_STRUCTURE_NAME(omniscia::core::ecs, ECS_PlayerCollectorController, _enabled, _collected);

#endif
