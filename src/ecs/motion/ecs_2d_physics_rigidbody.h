/**
 * @file 
 * ecs_2d_physics_rigidbody.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _ECS_2D_PHYSICS_RIGIDBODY_H_
#define _ECS_2D_PHYSICS_RIGIDBODY_H_

#include <array>
#include <memory>
#include <iostream>

#include "ecs_movable_aabb_collider.h"
#include "ecs_physics_positioned.h"
#include "ecs_acceleration.h"
#include "ecs_component.tpp"
#include "ecs_positioned.h"
#include "ecs_velocity.h"
#include "ecs_friction.h"
#include "ecs_system.h" 
#include "timesystem.h"
#include "entity.h"

namespace omniscia::core::ecs {
    using namespace omni::types;
    
    /**
     * @brief ECS_2DPhysicsRigidbody - component used for 
     * managing all 2d based physics, controls position of the enity, taking into a count
     * collisions, friction acceleration, velocity and etc.
    */
    class ECS_2DPhysicsRigidbody : public ECS_Component {
        private:
            /**
             * @brief Pointer to the parent entity 
             * instance, used for reindexing and time sync 
            */
            Entity* _parent;

            /** @brief ECS_Index of the Positioned component */
            ECS_Index<ECS_Positioned> _posIndex;
            
            /** @brief ECS_Index of the Movable aabb collider component */
            ECS_Index<ECS_MovableAABBCollider> _colliderIndex;
            
            /** @brief ECS_Index of the velocity component */
            ECS_Index<ECS_Velocity> _velocityIndex;
            
            /** @brief ECS_Index of the acceleration component */
            ECS_Index<ECS_Acceleration> _accelerationIndex;
            
            /** @brief ECS_Index of the friction component */
            ECS_Index<ECS_Friction> _frictionIndex;
            
            /** @brief ECS_Index of the physics positioned component */
            ECS_Index<ECS_PhysicsPositioned> _physicsPositionedIndex;
            
        public:
            /* Some evil macros */
            OMNISCIA_STRING_REPRESENTATION(ECS_2DPhysicsRigidbody, this->_parent);
            OMNISCIA_OFSTREAM_REPRESENTATION(ECS_2DPhysicsRigidbody, self._parent);

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

            ECS_2DPhysicsRigidbody();

            /**
             * @brief Method used for updating 
             * component, does some calculations
             * updates all data
             * 
             * For example: position, velocity, etc. 
            */
            void update();

            /**
             * @brief Method used for late update, runs after main
             * update method
            */
            void late_update();
            
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
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_2DPhysicsRigidbody>(*this));
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
     * @brief ECS_2DPhysicsRigidbodySystem - System 
     * class used for managing all updates and data for
     * all active ECS_2DPhysicsRigidbody type components
    */
    class ECS_2DPhysicsRigidbodySystem : public ECS_System<ECS_2DPhysicsRigidbody> {
        private:
            /**
             * @brief Hidden default constructor
            */
            ECS_2DPhysicsRigidbodySystem() : ECS_System<ECS_2DPhysicsRigidbody>() {};
            
            /**
             * @brief Disabled default copy constructor
            */
            ECS_2DPhysicsRigidbodySystem(ECS_2DPhysicsRigidbodySystem const&) = delete;
            
            /**
             * @brief Disabled default assignment operator
            */         
            void operator=(ECS_2DPhysicsRigidbodySystem const&) = delete;

        public:
            /**
             * @brief Main update method, updates 
             * all currently assigned components
            */
            void update() {
                if(!_enabled)
                    return;

                for(ECS_2DPhysicsRigidbody* comp : _components) {
                    if(comp == nullptr)
                        continue;

                    Entity* parent = comp->get_parent();

                    if(DebugUI::get_instance().get_metrics()._isTimeJump) {
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
             * @brief Late update method
             * runs after main update method
            */
            void late_update() {
                
                for(ECS_2DPhysicsRigidbody* comp : _components) {
                    if(comp == nullptr)
                        continue;

                    Entity* parent = comp->get_parent();

                    if(DebugUI::get_instance().get_metrics()._isTimeJump) {
                        if(parent == nullptr)
                            continue;
                        
                        const EntityTimeType timeType = parent->get_time_type();
                        
                        if(timeType == EntityTimeType::STATIC)
                            comp->late_update();
                    } else {
                        comp->late_update();
                    }
                }

                std::for_each(_components.begin(), _components.end(), [&](ECS_2DPhysicsRigidbody* comp) {
                    comp->late_update();
                });
            }

            /**
             * @brief Get the singleton instance of the ECS_2DPhysicsRigidbodySystem system
             * 
             * @return Reference to singleton instance of the ECS_2DPhysicsRigidbodySystem system
            */
            static ECS_2DPhysicsRigidbodySystem& get_instance() {
                static ECS_2DPhysicsRigidbodySystem instance;
                return instance;
            }
    };
}

#endif