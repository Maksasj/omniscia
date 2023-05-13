#ifndef _ECS_TEXT_RENDERER_H_
#define _ECS_TEXT_RENDERER_H_

#include <array>
#include <memory>
#include <iostream>
#include <cmath>

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
#include "ecs_instancing_renderer.h"
#include "font_manager.h"

namespace omniscia::core::ecs {
    using namespace omni::types;
    using namespace omniscia::gfx; 
    using namespace omniscia::gfx::sprite;

    class ECS_TextRenderer : public ECS_InstancingRenderer {
        private:
            std::string _textToRender;
            FontAsset* _fontAsset;

            f32 _lineLetterSpacing; 
            f32 _rowLineSpacing;
            u64 _charactersPerRow;

        public:
            void reindex(void* parent) override;

            ECS_TextRenderer(ECS_TextRenderer const& comp);

            ECS_TextRenderer(const std::string& fontId, const std::string& textToRender, const f32& lineLetterSpacing, const f32& rowLineSpacing, const u64& charactersPerRow, const u32& layer);

            void set_text_to_render(const std::string& textToRender, const f32& lineLetterSpacing, const f32& rowLineSpacing, const u64& charactersPerRow);

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_TextRenderer>(*this));
            }

            u64 byte_size() override {
                return sizeof(ECS_TextRenderer) - sizeof(Sprite) + _instancingSprite.byte_size();
            }
    };
}

#endif