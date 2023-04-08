#ifndef _ECS_PARALLAX_SPRITE_RENDERER_H_
#define _ECS_PARALLAX_SPRITE_RENDERER_H_

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

    class ECS_ParallaxSpriteRendererBack : public ECS_Component {
        private:
            u32 _layer;
            Entity* _parent;

            Sprite _sprite;

            f32 _layerOffset;
            std::function<f32(f32&)> _layerOffsetCallBack;
        public:
            void time_sync() override;

            ECS_ParallaxSpriteRendererBack(const std::string& texture_id, const u32& layer, const std::function<f32(f32&)>& layerOffsetCallBack);
            
            u32 get_layer() const;

            void render(const Shader *shader);

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_ParallaxSpriteRendererBack>(*this));
            }
    };

    class ECS_ParallaxSpriteRendererBackSystem : public ECS_System<ECS_ParallaxSpriteRendererBack> {
        private:
            ECS_ParallaxSpriteRendererBackSystem() {};
            ECS_ParallaxSpriteRendererBackSystem(ECS_ParallaxSpriteRendererBackSystem const&) {};
            void operator=(ECS_ParallaxSpriteRendererBackSystem const&) {};
        public:
            void render(const Shader* shader) {
                for(ECS_ParallaxSpriteRendererBack* comp : _components) {
                    comp->render(shader);
                }
            }

            static ECS_ParallaxSpriteRendererBackSystem& get_instance() {
                static ECS_ParallaxSpriteRendererBackSystem instance;
                return instance;
            }
    };
}

#endif