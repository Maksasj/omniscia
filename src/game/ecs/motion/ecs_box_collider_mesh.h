/**
 * @file 
 * ecs_box_collider_mesh.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _ECS_COMPONENT_BOX_COLLIDER_MESH_H_
#define _ECS_COMPONENT_BOX_COLLIDER_MESH_H_

#include <array>
#include <memory>
#include <iostream>

#include "ecs_component.tpp"
#include "controls.h"
#include "omni_types.tpp"
#include "entity.h"
 
namespace omniscia::core::ecs {
    using namespace omni::types;
    
    /*      .-------------------.
     *      |         ^         |
     *      |         | Y ranges|
     *      |         |         |
     *      |         |         |
     *      | X ranges|         |
     *      |<--------+-------->|
     *      |         |         |
     *      |         V         |
     *      .-------------------.
    */
   
    /**
     * @brief ECS_BoxColliderMesh - component used for
     * managing collision, this component stores
     * collision box of the entity(See commnet above)
    */
    class ECS_BoxColliderMesh : public ECS_Component {
        private:
            /**
             * @brief The range of the entity's
             * collision box on the x-axis
            */
            Vec2f _xRanges;

            /**
             * @brief The range of the entity's
             * collision box on the y-axis
            */
            Vec2f _yRanges;

        public:
            friend class omni::reflector::FieldFriendlyScope;
            friend class omni::reflector::Reflection<ECS_BoxColliderMesh>;

            /**
             * @brief Constructs a new ECS_BoxColliderMesh object
             * 
             * @param xRanges The range of the entity's collision box on the x-axis
             * @param yRanges The range of the entity's collision box on the y-axis
             */
            ECS_BoxColliderMesh(const Vec2f& xRanges, const Vec2f& yRanges);

            /**
             * @brief Gets the range of the entity's 
             * collision box on the x-axis
             * 
             * @return The range of the entity's 
             * collision box on the x-axis
            */
            Vec2f get_x_collision_ranges() const;

            /**
             * @brief Gets the range of the entity's 
             * collision box on the y-axis
             * 
             * @return The range of the entity's 
             * collision box on the y-axis
            */
            Vec2f get_y_collision_ranges() const;

            /**
             * @brief Method used for clonning single 
             * component instance, allocates copy of
             * the current component and returns pointer to it
             * 
             * @return pointer to the new component instance
            */
            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_BoxColliderMesh>(*this));
            }

            void _type_query(void* query) override {
                DebugFieldQuery::debug_component_edit_query<ECS_BoxColliderMesh>(*this);
            }
    };
}

OMNI_ADAPT_STRUCTURE_NAME(omniscia::core::ecs, ECS_BoxColliderMesh, _enabled, _xRanges, _yRanges);

#endif