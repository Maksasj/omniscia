#ifndef _ECS_POPUP_RENDERER_H_
#define _ECS_POPUP_RENDERER_H_

#include <array>
#include <memory>
#include <iostream>

#include "ecs_sprite_animation.h"
#include "ecs_pro_renderer.h"
#include "ecs_component.tpp"
#include "ecs_sprite_flip.h"
#include "ecs_positioned.h"
#include "ecs_sprite_animation_manual.h"
#include "ecs_system.h"
#include "ecs_scaled.h"
#include "controls.h"
#include "entity.h"
#include "sprite.h"
#include "shader.h"

namespace omniscia::core::ecs {
    using namespace omniscia::gfx::sprite;
    using namespace omniscia::gfx; 

    class ECS_PopupRenderer : public ECS_ProRenderer {
        private:
            Entity* _parent;

            Sprite _sprite;

            ECS_SpriteAnimationManual _animationComp;
            
            ECS_Index<ECS_Positioned> _posIndex;
            ECS_Index<ECS_Scaled> _scaleIndex;

            Vec2f _offset;

        public:
            void time_sync() override;
            void reindex(void* parent) override;

            ECS_PopupRenderer(const std::string& textureId, const u32& layer, const std::string& popupAnimation);

            void render() override;

            void set_offset(const Vec2f& offset) {
                _offset = offset;
            }

            void set_frame(const u64& frame) {
                _animationComp.set_frame(frame);
            }

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_PopupRenderer>(*this));
            }

            u64 byte_size() override {
                return sizeof(ECS_PopupRenderer) - sizeof(Sprite) + _sprite.byte_size();
            }
    };
}

#endif