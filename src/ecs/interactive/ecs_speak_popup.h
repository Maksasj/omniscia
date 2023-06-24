#ifndef _ECS_COMPONENT_SPEAK_POPUP_H_
#define _ECS_COMPONENT_SPEAK_POPUP_H_

#include "cutscene.h"
#include "ecs_popup.h"

namespace omniscia::core::ecs {
    using namespace omni::types;
    using namespace omniscia::core;

    class ECS_SpeakPopup : public ECS_Popup {  
        std::string _dialogueCutsceneId;

        public:
            friend class omni::reflector::FieldFriendlyScope;
            friend class omni::reflector::Reflection<ECS_SpeakPopup>;

            ECS_SpeakPopup(const std::string& dialogueCutsceneId);

            ECS_SpeakPopup(ECS_SpeakPopup const& comp);

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_SpeakPopup>(*this));
            }

            void _type_query(void* query) override {
                DebugFieldQuery::debug_component_edit_query<ECS_SpeakPopup>(*this);
            }
    };
}

OMNI_ADAPT_STRUCTURE_NAME(omniscia::core::ecs, ECS_SpeakPopup, _enabled, _cooldown, _timer, _animationId, _offset, _visibilityDistance, _dialogueCutsceneId);

#endif
