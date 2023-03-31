#ifndef _ECS_SPRITE_RENDERER_H_
#define _ECS_SPRITE_RENDERER_H_

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

    class ECS_SpriteRenderer : public ECS_Component {
        private:
            u32 _layer;
            Entity* _parent;

            ECS_Index<ECS_Positioned> _posIndex;
            ECS_Index<ECS_Scaled> _scaleIndex;
            Sprite _sprite;
        public:
            void reindex(void* parent) override;
            void time_sync() override;

            ECS_SpriteRenderer(const std::string& texture_id, const u32& layer);
            
            u32 get_layer() const;

            void render(const Shader *shader);

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_SpriteRenderer>(*this));
            }
    };

    class ECS_SpriteRendererSystem : public ECS_System<ECS_SpriteRenderer> {
        private:
            ECS_SpriteRendererSystem() {};
            ECS_SpriteRendererSystem(ECS_SpriteRendererSystem const&) {};
            void operator=(ECS_SpriteRendererSystem const&) {};
        public:
            void render(Shader* shader) {
                for(ECS_SpriteRenderer* comp : _components) {
                    comp->render(shader);
                }
            }

            static ECS_SpriteRendererSystem& get_instance() {
                static ECS_SpriteRendererSystem instance;
                return instance;
            }
    };
}

#endif