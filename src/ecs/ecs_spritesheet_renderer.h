#ifndef _ECS_SPRITESHEET_RENDERER_H_
#define _ECS_SPRITESHEET_RENDERER_H_

#include <array>
#include <memory>
#include <iostream>

#include "entity.h"

#include "ecs_system.h" 

#include "sprite.h"
#include "shader.h"
#include "ecs_component.tpp"
#include "controls.h"
#include "ecs_positioned.h"
#include "ecs_scaled.h"
#include "ecs_sprite_animation.h"

namespace omniscia::core::ecs {
    using namespace omniscia::renderer::sprite;
    using namespace omniscia::renderer; 

    class ECS_SpriteSheetRenderer : public ECS_Component {
        private:
            u32 _layer;
            std::reference_wrapper<Entity> _parent;

            ECS_Index<ECS_SpriteAnimation> _animationIndex;
            ECS_Index<ECS_Positioned> _posIndex;
            ECS_Index<ECS_Scaled> _scaleIndex;

            Sprite _sprite;
        public:
            ECS_SpriteSheetRenderer(const std::string& texture_id, Entity& parent, const u32& layer);
            void reindex(void* parent) override;
            void time_sync() override;

            u32 get_layer() const;

            void render(const Shader *shader);

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_SpriteSheetRenderer>(*this));
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