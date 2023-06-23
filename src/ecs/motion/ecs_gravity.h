/**
 * @file 
 * ecs_gravity.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _ECS_COMPONENT_GRAVITY_H_
#define _ECS_COMPONENT_GRAVITY_H_

#include <array>
#include <memory>
#include <iostream>

#include "ecs_acceleration.h"
#include "ecs_component.tpp"
#include "ecs_velocity.h"
#include "timesystem.h"
#include "ecs_system.h"
#include "controls.h"
#include "entity.h"

namespace omniscia::core::ecs {
    using namespace omni::types;
    using namespace omniscia::core;

    /**
     * @brief ECS_Gravity - component that used
     * for gravity calculations, applies gravity to 
     * entity velocity and acceleration
    */
    class ECS_Gravity : public ECS_Component {
        private:
            /**
             * @brief Pointer to the parent entity 
             * instance, used for reindexing and time sync 
            */
            Entity* _parent;

            /** @brief Gravity acceleration speed */
            f32 _gravitationalAcceleration;

            /** @brief ECS_Index of the velocity component */
            ECS_Index<ECS_Velocity> velocityIndex;
            
            /** @brief ECS_Index of the acceleration component */
            ECS_Index<ECS_Acceleration> accelerationIndex;

        public:
            /* Some evil macros */
            OMNISCIA_STRING_REPRESENTATION(ECS_Gravity, this->_parent << " " << this->_gravitationalAcceleration);
            OMNISCIA_OFSTREAM_REPRESENTATION(ECS_Gravity, self._parent << " " << self._gravitationalAcceleration);

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

            /** @brief Default constructor of the ECS_Gravity component */
            ECS_Gravity();

            /**
             * @brief Update method that applies gravity
             * acceleration to the entity 
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
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_Gravity>(*this));
            }

            Entity* get_parent() {
                return _parent;
            }
            
            /**
             * @brief Virtual method used for 
             * calculating byte size of the component
             * 
             * @return byte size of the component
            */
            void _type_query(void* query) override {

            }
    };

    /**
     * @brief ECS_GravitySystem - System 
     * class used for managing all updates and data for
     * all active ECS_Gravity type components
    */
    class ECS_GravitySystem : public ECS_System<ECS_Gravity> {
        private:
            /**
             * @brief Hidden default constructor
            */
            ECS_GravitySystem() : ECS_System<ECS_Gravity>() {};
            
            /**
             * @brief Disabled default copy constructor
            */
            ECS_GravitySystem(ECS_GravitySystem const&) = delete;
            
            /**
             * @brief Disabled default assignment operator
            */
            void operator=(ECS_GravitySystem const&) = delete;

        public:
            /**
             * @brief Main update method, updates 
             * all currently assigned components
            */
            void update() {
                if(!_enabled)
                    return;

                for(ECS_Gravity* comp : _components) {
                    if(comp == nullptr)
                        continue;

                    Entity* parent = comp->get_parent();

                    if(DebugInfo::get_instance().get_metrics()._isTimeJump) {
                        if(parent == nullptr)
                            continue;
                        
                        const EntityTimeType timeType = parent->get_time_type();
                        
                        if(timeType == EntityTimeType::STATIC)
                            comp->update();
                    } else {
                        comp->update();
                    }
                }

            }

            /**
             * @brief Get the singleton instance of the ECS_GravitySystem system
             * 
             * @return Reference to singleton instance of the ECS_GravitySystem system
            */
            static ECS_GravitySystem& get_instance() {
                static ECS_GravitySystem instance;
                return instance;
            }
    };
}

#endif
