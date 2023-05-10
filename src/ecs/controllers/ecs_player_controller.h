/**
 * @file 
 * ecs_player_controller.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _ECS_COMPONENT_PLAYER_CONTOLLER_H_
#define _ECS_COMPONENT_PLAYER_CONTOLLER_H_

#include <array>
#include <memory>
#include <iostream>

#include "ecs_sprite_animation.h"
#include "ecs_acceleration.h"
#include "ecs_component.tpp"
#include "ecs_sprite_flip.h"
#include "ecs_velocity.h"
#include "ecs_system.h"
#include "timesystem.h"
#include "controls.h"
#include "entity.h"

namespace omniscia::core::ecs {
    using namespace omni::types;
    using namespace omniscia::core;

    /**
     * @brief ECS_PlayerController - components that manages
     * player ai, controls movement and other things, this is a
     * core component of the player ai
    */
    class ECS_PlayerController : public ECS_Component {
        private:
            /**
             * @brief Pointer to the parent entity 
             * instance, used for reindexing and time sync 
            */
            Entity* _parent;

            /** @brief ECS_Index of the velocity component */
            ECS_Index<ECS_Velocity> velocityIndex;
            
            /** @brief ECS_Index of the acceleration component */
            ECS_Index<ECS_Acceleration> accelerationIndex;
            
            /** @brief ECS_Index of the sprite flip component */
            ECS_Index<ECS_SpriteFlip> spriteFlipIndex;
            
            /** @brief ECS_Index of the sprite animation component */
            ECS_Index<ECS_SpriteAnimation> spriteAnimationIndex;

        public:
            /* Some evil macros */
            OMNISCIA_STRING_REPRESENTATION(ECS_PlayerController, this->_parent);
            OMNISCIA_OFSTREAM_REPRESENTATION(ECS_PlayerController, self._parent);

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
             * @brief Default constructor of the ECS_PlayerController component
            */
            ECS_PlayerController();

            /**
             * @brief Method used for updating player velocity, and controll it movement
            */
            void control();

            /**
             * @brief Method used for clonning single 
             * component instance, allocates copy of
             * the current component and returns pointer to it
             * 
             * @return pointer to the new component instance
            */
            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_PlayerController>(*this));
            }

            /**
             * @brief Virtual method used for 
             * calculating byte size of the component
             * 
             * @return byte size of the component
            */
            u64 byte_size() override {
                return sizeof(ECS_PlayerController);
            }
    };

    /**
     * @brief ECS_PlayerControllerSystem - System 
     * class used for managing all updates and data for
     * all active ECS_PlayerController type components
    */
    class ECS_PlayerControllerSystem : public ECS_System<ECS_PlayerController> {
        private:
            /**
             * @brief Hidden default constructor
            */
            ECS_PlayerControllerSystem() : ECS_System<ECS_PlayerController>() {};
            
            /**
             * @brief Disabled default copy constructor
            */
            ECS_PlayerControllerSystem(ECS_PlayerControllerSystem const&) = delete;
            
            /**
             * @brief Disabled default assignment operator
            */
            void operator=(ECS_PlayerControllerSystem const&) = delete;
        
        public:
            /**
             * @brief Main update method, updates 
             * all currently assigned components
            */
            void update() {
                if(!_enabled)
                    return;

                for(ECS_PlayerController* comp : _components) {
                    comp->control();
                }
            }

            /**
             * @brief Get the singleton instance of the ECS_PlayerControllerSystem system
             * 
             * @return Reference to singleton instance of the ECS_PlayerControllerSystem system
            */
            static ECS_PlayerControllerSystem& get_instance() {
                static ECS_PlayerControllerSystem instance;
                return instance;
            }
    };
}

#endif
