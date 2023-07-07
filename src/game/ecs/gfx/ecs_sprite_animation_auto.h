#ifndef _ECS_SPRITE_ANIMATION_AUTO_H_
#define _ECS_SPRITE_ANIMATION_AUTO_H_

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

    class ECS_SpriteAnimationAuto : public ECS_SpriteAnimation {
        public:
            friend class omni::reflector::FieldFriendlyScope;
            friend class omni::reflector::Reflection<ECS_SpriteAnimationAuto>;

            ECS_SpriteAnimationAuto(const std::string &animationId);

            void update() override;

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_SpriteAnimationAuto>(*this));
            }

            void _type_query(void* query) override {
                DebugFieldQuery::debug_component_edit_query<ECS_SpriteAnimationAuto>(*this);
            }
    };
}

OMNI_ADAPT_STRUCTURE_NAME(omniscia::core::ecs, ECS_SpriteAnimationAuto, _enabled, _currentFrame, _animationId, _tick);

#endif