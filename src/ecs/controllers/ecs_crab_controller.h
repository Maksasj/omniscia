/**
 * @file 
 * ecs_crab_controller.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

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
    using namespace omni::types;
    using namespace omniscia::core;

    /**
     * @brief ECS_CrabController - components that manages
     * crab ai, controls movement and other things, this is a
     * core component of the crab ai
    */
    class ECS_CrabController : public ECS_StateMachineBase {
        private:
            /**
             * @brief Pointer to the parent entity 
             * instance, used for reindexing and time sync 
            */
            Entity* _parent;
            
            /** @brief ECS_Index of the sprite flip component */
            ECS_Index<ECS_SpriteFlip> _spriteFlipIndex;
            
            /** @brief ECS_Index of the acceleration component */
            ECS_Index<ECS_Acceleration> _accelerationIndex;
            
            /** @brief ECS_Index of the sprite animation component */
            ECS_Index<ECS_SpriteAnimation> _spriteAnimationIndex;
            
            /** @brief ECS_Index of the movable aabb collider component */
            ECS_Index<ECS_MovableAABBCollider> _colliderIndex; 
            
            /** @brief ECS_Index of the velocity component */
            ECS_Index<ECS_Velocity> _velocityIndex; 
            
            /** @brief ECS_Index of the sound emitter component */
            ECS_Index<ECS_SoundEmitter> _soundEmitterIndex;

        public:
            /* Some evil macros */
            OMNISCIA_STRING_REPRESENTATION(ECS_CrabController, this->_parent);
            OMNISCIA_OFSTREAM_REPRESENTATION(ECS_CrabController, self._parent);

            /**
             * @brief Method used for time 
             * synchronization of the component
             * instance, binds component to the
             * system
            */
            void time_sync() override;

            /**
             * @brief Method that reindexes all indexes
             * that are required by this component,
             * also updates pointer to the parent entity index
             * 
             * @param parent - pointer to the parent 
             * entity instance
            */
            void reindex(void* parent) override;

            /**
             * @brief Default constructor of the 
             * ECS_CrabController component
            */
            ECS_CrabController();

            /** @brief Update method for crab run left state */
            void crab_run_left_state();

            /** @brief Update method for crab run right state */
            void crab_run_right_state();
            
            /** @brief Update method for crab idle state */
            void crab_idle_state();

            /**
             * @brief Method used for clonning single 
             * component instance, allocates copy of
             * the current component and returns pointer to it
             * 
             * @return pointer to the new component instance
            */
            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_CrabController>(*this));
            }

            /**
             * @brief Virtual method used for 
             * calculating byte size of the component
             * 
             * @return byte size of the component
            */
            u64 byte_size() override {
                return sizeof(ECS_CrabController);
            }
    };
}

#endif
