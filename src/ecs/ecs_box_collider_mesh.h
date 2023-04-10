#ifndef _ECS_COMPONENT_BOX_COLLIDER_MESH_H_
#define _ECS_COMPONENT_BOX_COLLIDER_MESH_H_

#include <array>
#include <memory>
#include <iostream>

#include "ecs_component.tpp"
#include "controls.h"
#include "types.tpp"
#include "entity.h"
 
namespace omniscia::core::ecs {
    
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
 
    class ECS_BoxColliderMesh : public ECS_Component {
        private:
            Vec2f _xRanges;
            Vec2f _yRanges;
        public:
            ECS_BoxColliderMesh(const Vec2f& xRanges, const Vec2f& yRanges);

            Vec2f get_x_collision_ranges() const;
            Vec2f get_y_collision_ranges() const;

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_BoxColliderMesh>(*this));
            }

            u64 byte_size() override {
                return sizeof(ECS_BoxColliderMesh);
            }
    };
}

#endif