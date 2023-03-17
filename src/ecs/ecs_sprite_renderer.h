#ifndef _ECS_SPRITE_RENDERER_H_
#define _ECS_SPRITE_RENDERER_H_

#include <array>
#include <memory>
#include <iostream>

#include "entity.h"

#include "ecs_system.h" 

#include "sprite.h"
#include "shader.h"
#include "ecs_component.tpp"
#include "controls.h"

#include "ecs_scaled.h"
#include "ecs_positioned.h"

namespace omniscia::core::ecs {
    using namespace omniscia::renderer::sprite;
    using namespace omniscia::renderer; 

    class ECS_SpriteRenderer : public ECS_Component {
        private:
            u32 _layer;
            std::reference_wrapper<Entity> _parent;

            ECS_Index<ECS_Positioned> _posIndex;
            ECS_Index<ECS_Scaled> _scaleIndex;
            Sprite _sprite;
        public:
            void reindex(void* parent) override {
                _parent = *(Entity*)parent;

                _posIndex = _parent.get().index<ECS_Positioned>();
                _scaleIndex = _parent.get().index<ECS_Scaled>();
            }

            void time_sync() override;

            u32 get_layer() const {
                return _layer;
            }

            ECS_SpriteRenderer(const std::string& texture_id, Entity& parent, const u32& layer);

            void render(const Shader *shader) {
                Vec3f position = {0.0, 0.0, 0.0};
                Vec2f scale = {1.0, 1.0};

                if(_posIndex.is_success()) {
                    ECS_Positioned &positionComp = _parent.get().ref_unsafe(_posIndex);

                    position = positionComp.get_pos();
                }

                if(_scaleIndex.is_success()) {
                    ECS_Scaled &scaleComp = _parent.get().ref_unsafe(_scaleIndex);

                    scale = scaleComp.get_scale();
                }

                _sprite.render(shader, position, scale);
            }

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