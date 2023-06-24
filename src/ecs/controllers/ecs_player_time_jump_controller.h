/**
 * @file 
 * ecs_player_time_jump_controller.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _ECS_COMPONENT_PLAYER_TIME_JUMP_CONTROLLER_H_
#define _ECS_COMPONENT_PLAYER_TIME_JUMP_CONTROLLER_H_

#include <array>
#include <memory>
#include <iostream>

#include "ecs_movable_aabb_collider.h"
#include "ecs_acceleration.h"
#include "ecs_component.tpp"
#include "ecs_velocity.h"
#include "ecs_system.h"
#include "timesystem.h"
#include "controls.h"
#include "entity.h"
#include "debug_info.h"

namespace omniscia::core::ecs {
    using namespace omni::types;
    using namespace omniscia::core;

    /**
     * @brief ECS_PlayerTimeJumpController - component
     * that manages time jumps, for now only time jump
     * into the past, for now only works with player
    */
    class ECS_PlayerTimeJumpController : public ECS_Component {
        private:
            /**
             * @brief Pointer to the parent entity 
             * instance, used for reindexing and time sync 
            */
            Entity* _parent;

            /** @brief ECS_Index of the velocity component */
            ECS_Index<ECS_Velocity> velocityIndex;

            /** @brief ECS_Index of the movable aabb collider component */
            ECS_Index<ECS_MovableAABBCollider> movableAABBColliderIndex;

        public:
            friend class omni::reflector::FieldFriendlyScope;
            friend class omni::reflector::Reflection<ECS_PlayerTimeJumpController>;

            /**
             * @brief Method used for time 
             * synchronization of the component
             * instance, binds component to the
             * system
            */
            void time_sync() override;

            /**
             * @brief Default ECS_PlayerTimeJumpController component constructor
            */
            ECS_PlayerTimeJumpController();

            /**
             * @brief Method used for updating all time manipulation, sync systems
             * game state buffering and etc.
            */
            void update();

            Entity* get_parent() {
                return _parent;
            }

            /**
             * @brief Method used for clonning single 
             * component instance, allocates copy of
             * the current component and returns pointer to it
             * 
             * @return pointer to the new component instance
            */
            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_PlayerTimeJumpController>(*this));
            }

            void _type_query(void* query) override {
                DebugFieldQuery::debug_component_edit_query<ECS_PlayerTimeJumpController>(*this);
            }
    };
}

OMNI_ADAPT_STRUCTURE_NAME(omniscia::core::ecs, ECS_PlayerTimeJumpController, _enabled);

namespace omniscia::core::ecs {
    /**
     * @brief ECS_PlayerTimeJumpControllerSystem - System 
     * class used for managing all updates and data for
     * all active ECS_PlayerTimeJumpController type components
    */
    class ECS_PlayerTimeJumpControllerSystem : public ECS_System<ECS_PlayerTimeJumpController> {
        private:
            /**
             * @brief Hidden default constructor
            */
            ECS_PlayerTimeJumpControllerSystem() : ECS_System<ECS_PlayerTimeJumpController>() {};
            
            /**
             * @brief Disabled default copy constructor
            */
            ECS_PlayerTimeJumpControllerSystem(ECS_PlayerTimeJumpControllerSystem const&) = delete;
            
            /**
             * @brief Disabled default assignment operator
            */
            void operator=(ECS_PlayerTimeJumpControllerSystem const&) = delete;

        public:
            /**
             * @brief Main update method, updates 
             * all currently assigned components
            */
            void update() {
                if(!_enabled)
                    return;

                bool _ = std::all_of(_components.begin(), _components.end(), [&](ECS_PlayerTimeJumpController* comp) {
                    comp->update();
                    
                    if(DebugInfo::get_instance().get_metrics()._isTimeJump)
                        return false;
                    
                    return true;
                });
            }

            /**
             * @brief Get the singleton instance of the ECS_PlayerTimeJumpControllerSystem system
             * 
             * @return Reference to singleton instance of the ECS_PlayerTimeJumpControllerSystem system
            */
            static ECS_PlayerTimeJumpControllerSystem& get_instance() {
                static ECS_PlayerTimeJumpControllerSystem instance;
                return instance;
            }
    };
}

#endif
