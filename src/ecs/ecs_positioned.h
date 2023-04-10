#ifndef _ECS_COMPONENT_POSITIONED_H_
#define _ECS_COMPONENT_POSITIONED_H_

#include <array>
#include <memory>
#include <iostream>

#include "ecs_component.tpp"
#include "controls.h"
#include "entity.h"

namespace omniscia::core::ecs {
    class ECS_Positioned : public ECS_Component {
        private:
            Vec3f _pos;
        public:
            void reindex(void* parent) override;

            ECS_Positioned(const f32& x = 0.0f, const f32& y = 0.0f, const f32& z = 0.0f);
            ECS_Positioned(const Vec3f& pos);
            
            Vec3f get_pos() const;
            Vec3f& ref_pos();
            
            void set_pos(const Vec3f& newPos);
            void move_pos(const Vec3f& movedPos);

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_Positioned>(*this));
            }

            u64 byte_size() override {
                return sizeof(ECS_Positioned);
            }
    };
}

#endif