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

            /**
             * @brief Getter that returns old position of the entity
             * 
             * @return Vec3f old position of the entity
            */
            Vec3f get_old_position() const;

            /**
             * @brief Getter that returns new position of the entity
             * 
             * @return Vec3f new position of the entity
            */
            Vec3f get_new_position() const;

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
            u64 byte_size() override {
                return sizeof(ECS_2DPhysicsRigidbody);
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
            ECS_2DPhysicsRigidbodySystem() {};
            
            /**
             * @brief Hidden default copy constructor
            */
            ECS_2DPhysicsRigidbodySystem(ECS_2DPhysicsRigidbodySystem const&) {};
            
            /**
             * @brief Hidden default assignment operator
            */         
            void operator=(ECS_2DPhysicsRigidbodySystem const&) {};

        public:
            /**
             * @brief Main update method, updates 
             * all currently assigned components
            */
            void update() {
                for(ECS_2DPhysicsRigidbody* comp : _components) {
                    comp->update();
                }
            }

            /**
             * @brief Late update method
             * runs after main update method
            */
            void late_update() {
                for(ECS_2DPhysicsRigidbody* comp : _components) {
                    comp->late_update();
                }
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