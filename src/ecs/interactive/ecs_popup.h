#ifndef _ECS_COMPONENT_POPUP_H_
#define _ECS_COMPONENT_POPUP_H_

#include <array>
#include <memory>
#include <iostream>
#include <functional>

#include "ecs_acceleration.h"
#include "ecs_component.tpp"
#include "ecs_interactive.h"
#include "ecs_trigger_aabb_collider.h"
#include "ecs_popup_renderer.h"
#include "ecs_velocity.h"
#include "timesystem.h"
#include "ecs_system.h"
#include "controls.h"
#include "entity.h"
#include "debug_ui.h"

namespace omniscia::core::ecs {
    using namespace omni::types;
    using namespace omniscia::core;

    class ECS_Popup : public ECS_Interactive {        
        private:
            Entity* _parent;

            ECS_PopupRenderer _renderer;

            std::string _animationId;

            Vec2f _offset;
            f32 _visibilityDistance;

            ECS_Index<ECS_Positioned> _posIndex;

        public:
            void time_sync() override;
            void reindex(void* parent) override;

            ECS_Popup(  const f32& visibilityDistance,
                        const f32& scale,
                        const Vec2f& offset,
                        const std::string& textureId,
                        const std::string& popupAnimation,
                        const f32& cooldown,
                        const std::function<void(void)>& lambda);

            void update() override;

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_Popup>(*this));
            }

            u64 byte_size() override {
                return sizeof(ECS_Popup);
            }
    };
}

#endif
