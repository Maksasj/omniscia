#ifndef _ECS_COMPONENT_USE_POPUP_H_
#define _ECS_COMPONENT_USE_POPUP_H_

#include "cutscene.h"
#include "ecs_popup.h"

namespace omniscia::core::ecs {
    using namespace omni::types;
    using namespace omniscia::core;

    class ECS_UsePopup : public ECS_Popup {  
        const std::string _cutsceneId;

        public:
            ECS_UsePopup(const std::string& cutsceneId);

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_UsePopup>(*this));
            }

            void _type_query(void* query) override {

            }
    };
}

#endif
