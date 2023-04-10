#ifndef _ECS_COMPONENT_CRAB_CONTROLLER_H_
#define _ECS_COMPONENT_CRAB_CONTROLLER_H_

#include "ecs_state_machine_base.h"
#include "ecs_acceleration.h"
#include "ecs_sprite_flip.h"
#include "ecs_sprite_animation.h"
#include "ecs_movable_aabb_collider.h"
#include "ecs_sound_emitter.h"
#include "ecs_velocity.h"

namespace omniscia::core::ecs {
    using namespace omniscia::core;

    class ECS_CrabController : public ECS_StateMachineBase {
        private:
            Entity* _parent;
            
            ECS_Index<ECS_SpriteFlip> _spriteFlipIndex;
            ECS_Index<ECS_Acceleration> _accelerationIndex;
            ECS_Index<ECS_SpriteAnimation> _spriteAnimationIndex;
            ECS_Index<ECS_MovableAABBCollider> _colliderIndex; 
            ECS_Index<ECS_Velocity> _velocityIndex; 
            ECS_Index<ECS_SoundEmitter> _soundEmitterIndex;
        public:
            void reindex(void* parent) override;
            void time_sync() override;

            ECS_CrabController();

            void crab_run_left_state();
            void crab_run_right_state();
            void crab_idle_state();

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_CrabController>(*this));
            }

            u64 byte_size() override {
                return sizeof(ECS_CrabController);
            }
    };
}

#endif
