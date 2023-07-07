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
            friend class omni::reflector::FieldFriendlyScope;
            friend class omni::reflector::Reflection<ECS_Transparency>;

            ECS_Transparency(const f32& transparency = 1.0f);

            f32 get_transparency() const;

            f32& ref_transparency();

            void set_transparency(const f32& transparency);

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_Transparency>(*this));
            }

            void _type_query(void* query) override {
                DebugFieldQuery::debug_component_edit_query<ECS_Transparency>(*this);
            }
    };
}

OMNI_ADAPT_STRUCTURE_NAME(omniscia::core::ecs, ECS_Transparency, _enabled, _transparency);

#endif