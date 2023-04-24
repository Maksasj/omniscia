/**
 * @file 
 * ecs_player_jump.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _ECS_COMPONENT_PLAYER_JUMP_H_
#define _ECS_COMPONENT_PLAYER_JUMP_H_

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

namespace omniscia::core::ecs {
    using namespace omniscia::core;

    /**
     * @brief ECS_PlayerJump - component that used
     * for applying jump to the entity acceleration
     * and velocity
    */
    class ECS_PlayerJump : public ECS_Component {
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
            /* Some evil macros */
            OMNISCIA_STRING_REPRESENTATION(ECS_PlayerJump, this->_parent);
            OMNISCIA_OFSTREAM_REPRESENTATION(ECS_PlayerJump, self._parent);

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
             * @brief Default ECS_PlayerJump constructor 
            */
            ECS_PlayerJump();

            /**
             * @brief Method used for updating player jump velocity
            */
            void update();

            /**
             * @brief Method used for clonning single 
             * component instance, allocates copy of
             * the current component and returns pointer to it
             * 
             * @return pointer to the new component instance
            */
            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_PlayerJump>(*this));
            }

            /**
             * @brief Virtual method used for 
             * calculating byte size of the component
             * 
             * @return byte size of the component
            */
            u64 byte_size() override {
                return sizeof(ECS_PlayerJump);
            }
    };

    /**
     * @brief ECS_PlayerJumpSystem - System 
     * class used for managing all updates and data for
     * all active ECS_PlayerJump type components
    */
    class ECS_PlayerJumpSystem : public ECS_System<ECS_PlayerJump> {
        private:
            /**
             * @brief Hidden default constructor
            */
            ECS_PlayerJumpSystem() : ECS_System<ECS_PlayerJump>() {};
            
            /**
             * @brief Hidden default copy constructor
            */
            ECS_PlayerJumpSystem(ECS_PlayerJumpSystem const&) {};
            
            /**
             * @brief Hidden default assignment operator
            */
            void operator=(ECS_PlayerJumpSystem const&) {};

        public:
            /**
             * @brief Main update method, updates 
             * all currently assigned components
            */
            void update() {
                if(!_enabled)
                    return;

                for(ECS_PlayerJump* comp : _components) {
                    comp->update();
                }
            }

            /**
             * @brief Get the singleton instance of the ECS_PlayerJumpSystem system
             * 
             * @return Reference to singleton instance of the ECS_PlayerJumpSystem system
            */
            static ECS_PlayerJumpSystem& get_instance() {
                static ECS_PlayerJumpSystem instance;
                return instance;
            }
    };
}

#endif