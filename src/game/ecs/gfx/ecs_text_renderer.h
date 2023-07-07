#ifndef _ECS_TEXT_RENDERER_H_
#define _ECS_TEXT_RENDERER_H_

#include <array>
#include <memory>
#include <iostream>
#include <cmath>

#include "ecs/gfx/ecs_sprite_animation.h"
#include "ecs/gfx/ecs_pro_renderer.h"
#include "ecs/ecs_component.tpp"
#include "ecs/gfx/ecs_sprite_flip.h"
#include "ecs/motion/ecs_positioned.h"
#include "ecs/ecs_system.h"
#include "ecs/motion/ecs_scaled.h"
#include "controls.h"
#include "ecs/entity.h"
#include "gfx/instancing_sprite.h"
#include "gfx/shader.h"
#include "ecs/gfx/ecs_instancing_renderer.h"
#include "asset/font/font_manager.h"

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
            friend class omni::reflector::FieldFriendlyScope;
            friend class omni::reflector::Reflection<ECS_TextRenderer>;

            void reindex(void* parent) override;

            ECS_TextRenderer(ECS_TextRenderer const& comp);

            ECS_TextRenderer(const std::string& fontId, const std::string& textToRender, const f32& lineLetterSpacing, const f32& rowLineSpacing, const u64& charactersPerRow, const u32& layer);

            void set_text_to_render(const std::string& textToRender, const f32& lineLetterSpacing, const f32& rowLineSpacing, const u64& charactersPerRow);

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_TextRenderer>(*this));
            }

            void _type_query(void* query) override {
                DebugFieldQuery::debug_component_edit_query<ECS_TextRenderer>(*this);
            }
    };
}

OMNI_ADAPT_STRUCTURE_NAME(omniscia::core::ecs, ECS_TextRenderer, _enabled, _layer, _textToRender, _lineLetterSpacing, _rowLineSpacing, _charactersPerRow);

#endif