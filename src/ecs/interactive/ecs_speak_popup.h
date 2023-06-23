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
            ECS_SpeakPopup(const std::string& dialogueCutsceneId);

            ECS_SpeakPopup(ECS_SpeakPopup const& comp);

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_SpeakPopup>(*this));
            }

            void _type_query(void* query) override {

            }
    };
}

#endif
