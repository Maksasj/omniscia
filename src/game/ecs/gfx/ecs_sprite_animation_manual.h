#ifndef _ECS_SPRITE_ANIMATION_MANUAL_H_
#define _ECS_SPRITE_ANIMATION_MANUAL_H_

#include <array>
#include <memory>
#include <iostream>

#include "asset/animation/animation_manager.h"
#include "ecs/ecs_component.tpp"
#include "ecs/motion/ecs_positioned.h"
#include "ecs/ecs_system.h"
#include "ecs/motion/ecs_scaled.h"
#include "asset/animation/animation.h"
#include "controls.h"
#include "ecs/entity.h"
#include "gfx/sprite.h"
#include "gfx/shader.h"
#include "ecs/gfx/ecs_sprite_animation.h"

namespace omniscia::core::ecs {
    using namespace omni::types;
    using namespace omniscia::gfx; 
    using namespace omniscia::gfx::sprite;

    class ECS_SpriteAnimationManual : public ECS_SpriteAnimation {
        public:
            friend class omni::reflector::FieldFriendlyScope;
            friend class omni::reflector::Reflection<ECS_SpriteAnimationManual>;

            ECS_SpriteAnimationManual(const std::string &animationId);

            void update() override;

            void set_frame(const u64& frame);

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_SpriteAnimationManual>(*this));
            }

            void _type_query(void* query) override {
                DebugFieldQuery::debug_component_edit_query<ECS_SpriteAnimationManual>(*this);
            }
    };
}

OMNI_ADAPT_STRUCTURE_NAME(omniscia::core::ecs, ECS_SpriteAnimationManual, _enabled, _currentFrame, _animationId, _tick);

#endif