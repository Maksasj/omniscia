/**
 * @file 
 * ecs_physics_positioned.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _ECS_PHYSICS_POSITIONED_H_
#define _ECS_PHYSICS_POSITIONED_H_

#include <array>
#include <memory>
#include <iostream>

#include "ecs_component.tpp"
#include "ecs_system.h" 

namespace omniscia::core::ecs {
    using namespace omni::types;
    
    /**
     * @brief ECS_PhysicsPositioned - component used
     * for storing temporary position of the enitity
     * used only for physics calculations
    */
    class ECS_PhysicsPositioned : public ECS_Component {
        /* Update and late update stuff */

        /** @brief Old entity position */
        Vec3f _oldPosition;
        
        /** @brief New entity position */
        Vec3f _newPosition;

        public:
            /* Some evil macros */
            OMNISCIA_STRING_REPRESENTATION(ECS_PhysicsPositioned, this->_oldPosition << " " << this->_newPosition);
            OMNISCIA_OFSTREAM_REPRESENTATION(ECS_PhysicsPositioned, self._oldPosition << " " << self._newPosition);

            /**
             * @brief Default ECS_PhysicsPositioned component constructor 
            */
            ECS_PhysicsPositioned();

            /**
             * @brief Get the old entity position
             * 
             * @return Vec3f old entity position
            */
            Vec3f get_old_position() const;
            
            /**
             * @brief Get the new entity position
             * 
             * @return Vec3f new entity position
            */
            Vec3f get_new_position() const;

            /**
             * @brief Sets the old position of the entity
             * 
             * @param value to be set as and old entity position
            */
            void set_old_position(const Vec3f& value);
            
            /**
             * @brief Sets the new position of the entity
             * 
             * @param value to be set as and new entity position
            */
            void set_new_position(const Vec3f& value);

            /**
             * @brief Method used for clonning single 
             * component instance, allocates copy of
             * the current component and returns pointer to it
             * 
             * @return pointer to the new component instance
            */
            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_PhysicsPositioned>(*this));
            }

            /**
             * @brief Virtual method used for 
             * calculating byte size of the component
             * 
             * @return byte size of the component
            */
            u64 byte_size() override {
                return sizeof(ECS_PhysicsPositioned);
            }
    };
}

#endif