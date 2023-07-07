#ifndef _ECS_COMPONENT_USE_POPUP_H_
#define _ECS_COMPONENT_USE_POPUP_H_

#include "scene/cutscene/cutscene.h"
#include "ecs/interactive/ecs_popup.h"

namespace omniscia::core::ecs {
    using namespace omni::types;
    using namespace omniscia::core;

    class ECS_UsePopup : public ECS_Popup {  
        std::string _cutsceneId;

        public:
            friend class omni::reflector::FieldFriendlyScope;
            friend class omni::reflector::Reflection<ECS_UsePopup>;

            ECS_UsePopup(const std::string& cutsceneId);

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_UsePopup>(*this));
            }

            void _type_query(void* query) override {
                DebugFieldQuery::debug_component_edit_query<ECS_UsePopup>(*this);
            }
    };
}

OMNI_ADAPT_STRUCTURE_NAME(omniscia::core::ecs, ECS_UsePopup, _enabled, _cooldown, _timer, _animationId, _offset, _visibilityDistance, _cutsceneId);

#endif
