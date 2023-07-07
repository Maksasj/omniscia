#ifndef _ECS_COMPONENT_CHECKPOINT_POPUP_H_
#define _ECS_COMPONENT_CHECKPOINT_POPUP_H_

#include "scene/cutscene/cutscene.h"
#include "ecs/interactive/ecs_popup.h"

namespace omniscia::core::ecs {
    using namespace omni::types;
    using namespace omniscia::core;

    class ECS_CheckpointPopup : public ECS_Popup {  
        public:
            friend class omni::reflector::FieldFriendlyScope;
            friend class omni::reflector::Reflection<ECS_CheckpointPopup>;

            ECS_CheckpointPopup();

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_CheckpointPopup>(*this));
            }

            void _type_query(void* query) override {
                DebugFieldQuery::debug_component_edit_query<ECS_CheckpointPopup>(*this);
            }
    };
}

OMNI_ADAPT_STRUCTURE_NAME(omniscia::core::ecs, ECS_CheckpointPopup, _enabled, _cooldown, _timer, _animationId, _offset, _visibilityDistance);

#endif
