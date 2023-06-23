#ifndef _ECS_GUI_SPRITESHEET_RENDERER_H_
#define _ECS_GUI_SPRITESHEET_RENDERER_H_

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
#include "sprite.h"
#include "shader.h"

namespace omniscia::core::ecs {
    using namespace omni::types;
    using namespace omniscia::gfx; 
    using namespace omniscia::gfx::sprite;

    class ECS_GuiSpriteSheetRenderer : public ECS_ProRenderer {
        private:
            Entity* _parent;

            Sprite _sprite;

            ECS_Index<ECS_SpriteFlip> _spriteFlipIndex;
            ECS_Index<ECS_SpriteAnimation> _animationIndex;
            ECS_Index<ECS_Positioned> _posIndex;
            ECS_Index<ECS_Scaled> _scaleIndex;
            ECS_Index<ECS_Transparency> _transparencyIndex;

        public:
            void time_sync() override;
            void reindex(void* parent) override;

            ECS_GuiSpriteSheetRenderer(const std::string& textureId, const u32& layer);

            void render() override;

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_GuiSpriteSheetRenderer>(*this));
            }

            void _type_query(void* query) override {

            }
    };
}

#endif