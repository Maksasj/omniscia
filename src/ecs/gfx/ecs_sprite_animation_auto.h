#ifndef _ECS_SPRITE_ANIMATION_AUTO_H_
#define _ECS_SPRITE_ANIMATION_AUTO_H_

#include <array>
#include <memory>
#include <iostream>

#include "animation_manager.h"
#include "ecs_component.tpp"
#include "ecs_positioned.h"
#include "ecs_system.h"
#include "ecs_scaled.h"
#include "animation.h"
#include "controls.h"
#include "entity.h"
#include "sprite.h"
#include "shader.h"
#include "ecs_sprite_animation.h"

namespace omniscia::core::ecs {
    using namespace omni::types;
    using namespace omniscia::gfx; 
    using namespace omniscia::gfx::sprite;

    class ECS_SpriteAnimationAuto : public ECS_SpriteAnimation {
        public:
            ECS_SpriteAnimationAuto(const std::string &animationId);

            void update() override;

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_SpriteAnimationAuto>(*this));
            }

            void _type_query(void* query) override {

            }
    };
}

#endif