/**
 * @file 
 * ecs_acceleration.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _ECS_COMPONENT_ACCELERATION_H_
#define _ECS_COMPONENT_ACCELERATION_H_

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
     * @brief ECS_Acceleration - component used for
     * managing acceleration of the entity, primary
     * used by physics system(rigidbody)
    */
    class ECS_Acceleration : public ECS_Component {
        private:
            /** @brief Acceleration vector of the entity */
            Vec3f _acl;

        public:
            friend class omni::reflector::FieldFriendlyScope;
            friend class omni::reflector::Reflection<ECS_Acceleration>;

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
             * @brief Default constructor of the ECS_Acceleration component
             * 
             * @param aclX x vector of the acceleration
             * @param aclY y vector of the acceleration
             * @param aclZ z vector of the acceleration
            */
            ECS_Acceleration(const f32& aclX = 0.0f, const f32& aclY = 0.0f, const f32& aclZ = 0.0f);
            
            /**
             * @brief Default constructor of the ECS_Acceleration component
             * 
             * @param acl Input acceleration vector
            */
            ECS_Acceleration(const Vec3f& acl);

            Vec3f get_acceleration() const;
            Vec3f& ref_acceleration();
            void add_acceleration(Vec3f force);
            void set_acceleration(Vec3f acceleration);

            /**
             * @brief Method used for clonning single 
             * component instance, allocates copy of
             * the current component and returns pointer to it
             * 
             * @return pointer to the new component instance
            */
            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_Acceleration>(*this));
            }

            void _type_query(void* query) override {
                DebugFieldQuery::debug_component_edit_query<ECS_Acceleration>(*this);
            }
    };
}

OMNI_ADAPT_STRUCTURE_NAME(omniscia::core::ecs, ECS_Acceleration, _enabled, _acl);

#endif