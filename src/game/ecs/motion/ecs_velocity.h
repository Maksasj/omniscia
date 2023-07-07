/**
 * @file 
 * ecs_velocity.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _ECS_COMPONENT_VELOCITY_H_
#define _ECS_COMPONENT_VELOCITY_H_

#include <array>
#include <memory>
#include <iostream>

#include "ecs/ecs_component.tpp"
#include "controls.h"
#include "omni_types.tpp"
#include "ecs/entity.h"
 
namespace omniscia::core::ecs {
    using namespace omni::types;
    
    /**
     * @brief ECS_Velocity - component that used 
     * for storing entity velocity values, as well
     * as max velocity ranges, can be used
     * for velocity clamping
    */
    class ECS_Velocity : public ECS_Component {
        private:
            /**
             * @brief Velocity of the entity
            */
            Vec3f _vel;

            /**
             * @brief Velocity x axis ranges
            */
            Vec2f _velocityRangesX;
            
            /**
             * @brief Velocity y axis ranges
            */
            Vec2f _velocityRangesY;
            
        public:
            friend class omni::reflector::FieldFriendlyScope;
            friend class omni::reflector::Reflection<ECS_Velocity>;

            /**
             * @brief Default constructor for ECS_Velocity component
             * 
             * @param velX x velocity force
             * @param velY y velocity force
             * @param velZ z velocity force
            */
            ECS_Velocity(const f32& velX = 0.0f, const f32& velY = 0.0f, const f32& velZ = 0.0f);

            /**
             * @brief Default constructor for ECS_Velocity component
             * 
             * @param vel velocity force
             * @param velocityRangesX x axis velocity ranges
            */
            ECS_Velocity(const Vec3f& vel, const Vec2f& velocityRangesX);
            
            /**
             * @brief Default constructor for ECS_Velocity component
             * 
             * @param vel velocity force
             * @param velocityRangesX x axis velocity ranges
             * @param velocityRangesY y axis velocity ranges
            */
            ECS_Velocity(const Vec3f& vel, const Vec2f& velocityRangesX, const Vec2f& velocityRangesY);
            
            /**
             * @brief Default constructor for ECS_Velocity component
             * 
             * @param velocityRangesX x axis velocity ranges
             * @param velocityRangesY y axis velocity ranges
            */
            ECS_Velocity(const Vec2f& velocityRangesX, const Vec2f& velocityRangesY);

            /**
             * @brief Get the velocity of the entity
             * 
             * @return Vec3f entity velocity
            */
            Vec3f get_velocity() const;

            /**
             * @brief Get the reference velocity of the entity
             * 
             * @return Vec3f reference to the entity velocity
            */
            Vec3f& ref_velocity();

            /**
             * @brief Add velocity for to the velocity
             * 
             * @param force to be added to the velocity 
            */
            void add_velocity(Vec3f force);
            
            /**
             * @brief Set the entity velocity to specifc value
             * 
             * @param velocity to be set to entity
            */
            void set_velocity(Vec3f velocity);

            /**
             * @brief Clamps entity velocity to velocity ranges
            */
            void clamp_velocity();

            /**
             * @brief Method used for clonning single 
             * component instance, allocates copy of
             * the current component and returns pointer to it
             * 
             * @return pointer to the new component instance
            */
            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_Velocity>(*this));
            }

            void _type_query(void* query) override {
                DebugFieldQuery::debug_component_edit_query<ECS_Velocity>(*this);
            }
    };
}

OMNI_ADAPT_STRUCTURE_NAME(omniscia::core::ecs, ECS_Velocity, _enabled, _vel, _velocityRangesX, _velocityRangesY);

#endif