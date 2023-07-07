#ifndef _ECS_COMPONENT_CLOCK_PROGRESSION_BAR_CONTROLLER_H_
#define _ECS_COMPONENT_CLOCK_PROGRESSION_BAR_CONTROLLER_H_

#include "ecs_state_machine_base.h"
#include "ecs_acceleration.h"
#include "ecs_sprite_flip.h"
#include "ecs_sprite_animation.h"
#include "ecs_movable_aabb_collider.h"
#include "ecs_sound_emitter.h"
#include "ecs_velocity.h"
#include "ecs_text_renderer.h"
#include "ecs_sprite_animation_manual.h"

#include "debug_info.h"

namespace omniscia::core::ecs {
    using namespace omni::types;
    using namespace omniscia::core;

    class ECS_ClockProgressionBarController : public ECS_StateMachineBase {
        private:
            ECS_Index<ECS_SpriteAnimationManual> _spriteAnimationIndex;

        public:
            friend class omni::reflector::FieldFriendlyScope;
            friend class omni::reflector::Reflection<ECS_ClockProgressionBarController>;

            void time_sync() override;
            void reindex(void* parent) override;

            ECS_ClockProgressionBarController();

            void clock_progression_bar_update_state();

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_ClockProgressionBarController>(*this));
            }

            void _type_query(void* query) override {
                DebugFieldQuery::debug_component_edit_query<ECS_ClockProgressionBarController>(*this);
            }
    };
}

OMNI_ADAPT_STRUCTURE_NAME(omniscia::core::ecs, ECS_ClockProgressionBarController, _enabled);

#endif