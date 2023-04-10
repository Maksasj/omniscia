#ifndef _ECS_SPRITESHEET_RENDERER_H_
#define _ECS_SPRITESHEET_RENDERER_H_

#include <array>
#include <memory>
#include <iostream>

#include "ecs_sprite_animation.h"
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
    using namespace omniscia::gfx::sprite;
    using namespace omniscia::gfx; 

    class ECS_SpriteSheetRenderer : public ECS_Component {
        private:
            Entity* _parent;
            
            u32 _layer;

            ECS_Index<ECS_SpriteFlip> _spriteFlipIndex;
            ECS_Index<ECS_SpriteAnimation> _animationIndex;
            ECS_Index<ECS_Positioned> _posIndex;
            ECS_Index<ECS_Scaled> _scaleIndex;

            Sprite _sprite;
        public:
            void reindex(void* parent) override;
            void time_sync() override;
            
            ECS_SpriteSheetRenderer(const std::string& texture_id, const u32& layer);

            u32 get_layer() const;

            void render(const Shader *shader);

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_SpriteSheetRenderer>(*this));
            }

            u64 byte_size() override {
                return sizeof(ECS_SpriteSheetRenderer) - sizeof(Sprite) + _sprite.byte_size();
            }
    };

    class ECS_SpriteSheetRendererSystem : public ECS_System<ECS_SpriteSheetRenderer> {
        private:
            ECS_SpriteSheetRendererSystem() {};
            ECS_SpriteSheetRendererSystem(ECS_SpriteSheetRendererSystem const&) {};
            void operator=(ECS_SpriteSheetRendererSystem const&) {};
        public:
            void render(Shader* shader) {
                for(ECS_SpriteSheetRenderer* comp : _components) {
                    comp->render(shader);
                }
            }

            static ECS_SpriteSheetRendererSystem& get_instance() {
                static ECS_SpriteSheetRendererSystem instance;
                return instance;
            }
    };
}

#endif