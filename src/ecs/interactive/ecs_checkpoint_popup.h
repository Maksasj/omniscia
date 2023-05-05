#ifndef _ECS_COMPONENT_CHECKPOINT_POPUP_H_
#define _ECS_COMPONENT_CHECKPOINT_POPUP_H_

#include "cutscene.h"
#include "ecs_popup.h"

namespace omniscia::core::ecs {
    using namespace omni::types;
    using namespace omniscia::core;

    class ECS_CheckpointPopup : public ECS_Popup {  
        public:
            ECS_CheckpointPopup();

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_CheckpointPopup>(*this));
            }

            u64 byte_size() override {
                return sizeof(ECS_Popup);
            }
    };
}

#endif
