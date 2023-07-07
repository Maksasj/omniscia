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
            friend class omni::reflector::FieldFriendlyScope;
            friend class omni::reflector::Reflection<ECS_CrabController>;

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

            ECS_CrabController(ECS_CrabController const& comp) : ECS_StateMachineBase(comp) {
                
            }

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

            void _type_query(void* query) override {
                DebugFieldQuery::debug_component_edit_query<ECS_CrabController>(*this);
            }
    };
}

OMNI_ADAPT_STRUCTURE_NAME(omniscia::core::ecs, ECS_CrabController, _enabled);

#endif
