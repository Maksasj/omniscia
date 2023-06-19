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
            /* Some evil macros */
            OMNISCIA_STRING_REPRESENTATION(ECS_Acceleration, this->_acl);
            OMNISCIA_OFSTREAM_REPRESENTATION(ECS_Acceleration, self._acl);

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

            /**
             * @brief Virtual method used for 
             * calculating byte size of the component
             * 
             * @return byte size of the component
            */
            u64 byte_size() override {
                return sizeof(ECS_Acceleration);
            }
    };
}

#endif