/**
 * @file 
 * ecs_positioned.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _ECS_COMPONENT_POSITIONED_H_
#define _ECS_COMPONENT_POSITIONED_H_

#include <array>
#include <memory>
#include <iostream>

#include "ecs/ecs_component.tpp"
#include "controls.h"
#include "ecs/entity.h"

namespace omniscia::core::ecs {
    using namespace omni::types;
    
    /**
     * @brief ECS_Positioned - component that
     * stores entity position, used by a lot of
     * other compoents, such as rigidbody,'
     * renderers and others
    */
    class ECS_Positioned : public ECS_Component {
        private:
            /** @brief Position of the entity */
            Vec3f _pos;

        public:
            friend class omni::reflector::FieldFriendlyScope;
            friend class omni::reflector::Reflection<ECS_Positioned>;

            /**
             * @brief Default constructor of the ECS_Positioned component
             * 
             * @param x coordinate
             * @param y coordinate
             * @param z coordinate
            */
            ECS_Positioned(const f32& x = 0.0f, const f32& y = 0.0f, const f32& z = 0.0f);
            
            /**
             * @brief Default constructor of the ECS_Positioned component
             * 
             * @param pos position to be set to the entity
            */
            ECS_Positioned(const Vec3f& pos);
            
            /**
             * @brief Get the position of the entity
             * 
             * @return Vec3f position of the entity
            */
            Vec3f get_pos() const;
            
            /**
             * @brief Get the reference to the position of the entity
             * 
             * @return Vec3f reference to the position of the entity
            */
            Vec3f& ref_pos();
            
            /**
             * @brief Set the position of the entity to specific value
             * 
             * @param newPos position value to be set as entity position 
            */
            void set_pos(const Vec3f& newPos);
            
            /**
             * @brief Move entity by specific distance
             * 
             * @param movedPos distance
            */
            void move_pos(const Vec3f& movedPos);

            /**
             * @brief Method used for clonning single 
             * component instance, allocates copy of
             * the current component and returns pointer to it
             * 
             * @return pointer to the new component instance
            */
            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_Positioned>(*this));
            }

            void _type_query(void* query) override {
                DebugFieldQuery::debug_component_edit_query<ECS_Positioned>(*this);
            }
    };
}

OMNI_ADAPT_STRUCTURE_NAME(omniscia::core::ecs, ECS_Positioned, _enabled, _pos);

#endif