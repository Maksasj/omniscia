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
    using namespace omni::types;
    using namespace omniscia::gfx; 
    using namespace omniscia::gfx::sprite;

    class ECS_PopupRenderer : public ECS_ProRenderer {
        private:
            Entity* _parent;

            Sprite _sprite;

            ECS_SpriteAnimationManual _animationComp;
            
            ECS_Index<ECS_Positioned> _posIndex;
            f32 _scale;

            f32 _transparency;
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

            void set_scale(const f32& scale) {
                _scale = scale;
            }

            void set_transparency(const f32& transparency) {
                _transparency = transparency;
            }

            void clamp_transparency() {
                if(_transparency < 0.0f) _transparency = 0.0f;
                if(_transparency > 1.0f) _transparency = 1.0f;
            }

            f32 get_transparency() const {
                return _transparency;
            }

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_PopupRenderer>(*this));
            }
            
            void _type_query(void* query) override {

            }
    };
}

#endif