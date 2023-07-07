/**
 * @file 
 * ecs_friction.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _ECS_COMPONENT_FRICTION_H_
#define _ECS_COMPONENT_FRICTION_H_

#include <array>
#include <memory>
#include <iostream>

#include "ecs_component.tpp"
#include "controls.h"
#include "omni_types.tpp"
#include "entity.h"

namespace omniscia::core::ecs {
    using namespace omni::types;

    /**
     * @brief ECS_Friction - component used for
     * storing friction of the entity, used only
     * for storing
    */
    class ECS_Friction : public ECS_Component {
        private:
            /** @brief Friction of the entity */
            f32 _friction;

        public:
            friend class omni::reflector::FieldFriendlyScope;
            friend class omni::reflector::Reflection<ECS_Friction>;

            /**
             * @brief Default constructor of the ECS_Friction component
             * 
             * @param friction value to be set as entity friction
            */
            ECS_Friction(const f32& friction = -0.01f);

            /**
             * @brief Get the friction of the entity
             * 
             * @return f32 friction of the entity
            */
            f32 get_friction() const;

            /**
             * @brief Get the reference friction of the entity
             * 
             * @return f32 reference friction of the entity
            */
            f32& ref_friction();
            
            /**
             * @brief Sets the friction to specific value
             * 
             * @param friction value to be set as friction
            */
            void set_friction(const f32& friction);

            /**
             * @brief Method used for clonning single 
             * component instance, allocates copy of
             * the current component and returns pointer to it
             * 
             * @return pointer to the new component instance
            */
            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_Friction>(*this));
            }

            void _type_query(void* query) override {
                DebugFieldQuery::debug_component_edit_query<ECS_Friction>(*this);
            }
    };
}

OMNI_ADAPT_STRUCTURE_NAME(omniscia::core::ecs, ECS_Friction, _enabled, _friction);

#endif