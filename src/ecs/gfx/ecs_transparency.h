#ifndef _ECS_COMPONENT_TRANSPARENCY_H_
#define _ECS_COMPONENT_TRANSPARENCY_H_

#include <array>
#include <memory>
#include <iostream>

#include "ecs_component.tpp"
#include "controls.h"
#include "entity.h"

namespace omniscia::core::ecs {
    using namespace omni::types;
    
    class ECS_Transparency : public ECS_Component {
        private:
            f32 _transparency;

        public:
            ECS_Transparency(const f32& transparency = 1.0f);

            f32 get_transparency() const;

            f32& ref_transparency();

            void set_transparency(const f32& transparency);

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_Transparency>(*this));
            }

            u64 byte_size() override {
                return sizeof(ECS_Transparency);
            }
    };
}

#endif