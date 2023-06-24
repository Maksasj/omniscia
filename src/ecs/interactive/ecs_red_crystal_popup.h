#ifndef _ECS_COMPONENT_REDCRYSTAL_POPUP_H_
#define _ECS_COMPONENT_REDCRYSTAL_POPUP_H_

#include "cutscene.h"
#include "ecs_popup.h"

namespace omniscia::core::ecs {
    using namespace omni::types;
    using namespace omniscia::core;

    class ECS_RedCrystalPopup : public ECS_Popup {  
        public:
            friend class omni::reflector::FieldFriendlyScope;
            friend class omni::reflector::Reflection<ECS_RedCrystalPopup>;

            ECS_RedCrystalPopup();

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_RedCrystalPopup>(*this));
            }

            void _type_query(void* query) override {
                DebugFieldQuery::debug_component_edit_query<ECS_RedCrystalPopup>(*this);
            }
    };
}

OMNI_ADAPT_STRUCTURE_NAME(omniscia::core::ecs, ECS_RedCrystalPopup, _enabled, _cooldown, _timer, _animationId, _offset, _visibilityDistance);

#endif
