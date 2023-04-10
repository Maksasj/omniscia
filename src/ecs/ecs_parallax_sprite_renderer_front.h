#ifndef _ECS_PARALLAX_SPRITE_RENDERER_FRONT_H_
#define _ECS_PARALLAX_SPRITE_RENDERER_FRONT_H_

#include <array>
#include <memory>
#include <iostream>

#include "ecs_component.tpp"
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

    class ECS_ParallaxSpriteRendererFront : public ECS_Component {
        private:
            u32 _layer;
            Entity* _parent;

            Sprite _sprite;

            f32 _layerOffset;
            std::function<f32(f32&)> _layerOffsetCallBack;
        public:
            void time_sync() override;

            ECS_ParallaxSpriteRendererFront(const std::string& texture_id, const u32& layer, const std::function<f32(f32&)>& layerOffsetCallBack);
            
            u32 get_layer() const;

            void render(const Shader *shader);

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_ParallaxSpriteRendererFront>(*this));
            }

            u64 byte_size() override {
                return sizeof(ECS_ParallaxSpriteRendererFront);
            }
    };

    class ECS_ParallaxSpriteRendererFrontSystem : public ECS_System<ECS_ParallaxSpriteRendererFront> {
        private:
            ECS_ParallaxSpriteRendererFrontSystem() {};
            ECS_ParallaxSpriteRendererFrontSystem(ECS_ParallaxSpriteRendererFrontSystem const&) {};
            void operator=(ECS_ParallaxSpriteRendererFrontSystem const&) {};
        public:
            void render(const Shader* shader) {
                for(ECS_ParallaxSpriteRendererFront* comp : _components) {
                    comp->render(shader);
                }
            }

            static ECS_ParallaxSpriteRendererFrontSystem& get_instance() {
                static ECS_ParallaxSpriteRendererFrontSystem instance;
                return instance;
            }
    };
}

#endif