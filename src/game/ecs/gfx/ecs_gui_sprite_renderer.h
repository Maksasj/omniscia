#ifndef _ECS_GUI_SPRITE_RENDERER_H_
#define _ECS_GUI_SPRITE_RENDERER_H_

#include <array>
#include <memory>
#include <iostream>

#include "ecs_pro_renderer.h"
#include "ecs_component.tpp"
#include "ecs_positioned.h"
#include "ecs_system.h"
#include "ecs_scaled.h"
#include "controls.h"
#include "entity.h"
#include "sprite.h"
#include "shader.h"
#include "ecs_sprite_flip.h"

namespace omniscia::core::ecs {
    using namespace omni::types;
    using namespace omniscia::gfx; 
    using namespace omniscia::gfx::sprite;

    class ECS_GuiSpriteRenderer : public ECS_ProRenderer {
        private:

            Entity* _parent;
            ECS_Index<ECS_Positioned> _posIndex;
            ECS_Index<ECS_Scaled> _scaleIndex;
            ECS_Index<ECS_Transparency> _transparencyIndex;
            ECS_Index<ECS_SpriteFlip> _spriteFlipIndex;

            Sprite _sprite;

        public:
            friend class omni::reflector::FieldFriendlyScope;
            friend class omni::reflector::Reflection<ECS_GuiSpriteRenderer>;

            void time_sync() override;
            void reindex(void* parent) override;

            ECS_GuiSpriteRenderer(const std::string& textureId, const u32& layer);

            void set_texture_by_id(const std::string& textureId);

            void render() override;

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_GuiSpriteRenderer>(*this));
            }

            void _type_query(void* query) override {
                DebugFieldQuery::debug_component_edit_query<ECS_GuiSpriteRenderer>(*this);
            }
    };
}

OMNI_ADAPT_STRUCTURE_NAME(omniscia::core::ecs, ECS_GuiSpriteRenderer, _enabled, _layer);


#endif