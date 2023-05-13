#ifndef _ECS_COMPONENT_PLAYER_STAR_CONTROLLER_H_
#define _ECS_COMPONENT_PLAYER_STAR_CONTROLLER_H_

#include "ecs_state_machine_base.h"
#include "ecs_acceleration.h"
#include "ecs_sprite_flip.h"
#include "ecs_sprite_animation.h"
#include "ecs_movable_aabb_collider.h"
#include "ecs_sound_emitter.h"
#include "ecs_velocity.h"

#include "debug_ui.h"

namespace omniscia::core::ecs {
    using namespace omni::types;
    using namespace omniscia::core;

    class ECS_PlayerCollectorController : public ECS_StateMachineBase {
        private:
            i32 _collected;

        public:
            void time_sync() override;
            void reindex(void* parent) override;

            ECS_PlayerCollectorController();

            ECS_PlayerCollectorController(ECS_PlayerCollectorController const& comp);

            void player_collector_state();
            void collect();

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_PlayerCollectorController>(*this));
            }

            u64 byte_size() override {
                return sizeof(ECS_PlayerCollectorController);
            }
    };
}

#endif
