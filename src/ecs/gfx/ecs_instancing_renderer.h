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
#include "ecs_transparency.h"

namespace omniscia::core::ecs {
    using namespace omni::types;
    using namespace omniscia::gfx; 
    using namespace omniscia::gfx::sprite;

    class ECS_InstancingRenderer : public ECS_ProRenderer {
        protected:
            Entity* _parent;

            InstancingSprite _instancingSprite;
            std::vector<InstancingData> _instancingData;

            ECS_Index<ECS_SpriteFlip> _spriteFlipIndex;
            ECS_Index<ECS_SpriteAnimation> _animationIndex;
            ECS_Index<ECS_Positioned> _posIndex;
            ECS_Index<ECS_Scaled> _scaleIndex;
            ECS_Index<ECS_Transparency> _transparencyIndex;

        public:
            friend class omni::reflector::FieldFriendlyScope;
            friend class omni::reflector::Reflection<ECS_InstancingRenderer>;

            void time_sync() override;

            void reindex(void* parent) override;

            ECS_InstancingRenderer(const std::string& textureId, const u32& layer);

            void render() override;

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_InstancingRenderer>(*this));
            }

            void _type_query(void* query) override {
                DebugFieldQuery::debug_component_edit_query<ECS_InstancingRenderer>(*this);
            }
    };
}

OMNI_ADAPT_STRUCTURE_NAME(omniscia::core::ecs, ECS_InstancingRenderer, _enabled, _layer);

#endif