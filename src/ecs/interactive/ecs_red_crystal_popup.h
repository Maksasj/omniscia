#ifndef _ECS_COMPONENT_REDCRYSTAL_POPUP_H_
#define _ECS_COMPONENT_REDCRYSTAL_POPUP_H_

#include "cutscene.h"
#include "ecs_popup.h"

namespace omniscia::core::ecs {
    using namespace omni::types;
    using namespace omniscia::core;

    class ECS_RedCrystalPopup : public ECS_Popup {  
        public:
            ECS_RedCrystalPopup();

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_RedCrystalPopup>(*this));
            }

            void _type_query(void* query) override {

            }
    };
}

#endif
