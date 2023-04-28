#ifndef _ECS_INSTANCING_RENDERER_H_
#define _ECS_INSTANCING_RENDERER_H_

#include <array>
#include <memory>
#include <iostream>

#include "ecs_sprite_animation.h"
#include "ecs_pro_renderer.h"
#include "ecs_component.tpp"
#include "ecs_sprite_flip.h"
#include "ecs_positioned.h"
#include "ecs_system.h"
#include "ecs_scaled.h"
#include "controls.h"
#include "entity.h"
#include "instancing_sprite.h"
#include "shader.h"

namespace omniscia::core::ecs {
    using namespace omniscia::gfx::sprite;
    using namespace omniscia::gfx; 

    class ECS_InstancingRenderer : public ECS_ProRenderer {
        protected:
            Entity* _parent;

            InstancingSprite _instancingSprite;
            std::vector<InstancingData> _instancingData;

            ECS_Index<ECS_SpriteFlip> _spriteFlipIndex;
            ECS_Index<ECS_SpriteAnimation> _animationIndex;
            ECS_Index<ECS_Positioned> _posIndex;
            ECS_Index<ECS_Scaled> _scaleIndex;

        public:
            void time_sync() override;

            void reindex(void* parent) override;

            ECS_InstancingRenderer(const std::string& textureId, const u32& layer);

            void render() override;

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_InstancingRenderer>(*this));
            }

            u64 byte_size() override {
                return sizeof(ECS_InstancingRenderer) - sizeof(Sprite) + _instancingSprite.byte_size();
            }
    };
}

#endif