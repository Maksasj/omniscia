/**
 * @file 
 * ecs_scaled.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _ECS_COMPONENT_SCALED_H_
#define _ECS_COMPONENT_SCALED_H_

#include <array>
#include <memory>
#include <iostream>

#include "ecs_component.tpp"
#include "controls.h"
#include "entity.h"

namespace omniscia::core::ecs {
    using namespace omni::types;
    
    /**
     * @brief ECS_Scaled - component that
     * stores entity scale, used by a lot of
     * other compoents, such as rigidbody,'
     * renderers and others
    */
    class ECS_Scaled : public ECS_Component {
        private:
            /** @brief Scale of the entity */
            Vec2f _scale;

        public:
            friend class omni::reflector::FieldFriendlyScope;
            friend class omni::reflector::Reflection<ECS_Scaled>;

            /**
             * @brief Default constructor of the ECS_Scaled component
             * 
             * @param scaleX x coordinate scale
             * @param scaleY y coordinate scale
            */
            ECS_Scaled(const f32& scaleX = 0.0f, const f32& scaleY = 0.0f);
            
            /**
             * @brief Default constructor of the ECS_Scaled component
             * 
             * @param scale scale vector
             */
            ECS_Scaled(const Vec2f& scale);
            
            /**
             * @brief Get the scale of the entity
             * 
             * @return Vec2f scale of the entity
            */
            Vec2f get_scale() const;
            
            /**
             * @brief Sets the entity scale to specific value
             * 
             * @param newScale new scale to be set to entity scale 
            */
            void set_scale(const Vec2f& newScale);

            /**
             * @brief Method used for clonning single 
             * component instance, allocates copy of
             * the current component and returns pointer to it
             * 
             * @return pointer to the new component instance
            */
            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_Scaled>(*this));
            }

            void _type_query(void* query) override {
                DebugFieldQuery::debug_component_edit_query<ECS_Scaled>(*this);
            }
    };
}

OMNI_ADAPT_STRUCTURE_NAME(omniscia::core::ecs, ECS_Scaled, _enabled, _scale);

#endif