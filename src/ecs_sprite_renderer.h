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
#include "ecs_positioned.h"

namespace omniscia::core::ecs {
    using namespace omniscia::renderer::sprite;
    using namespace omniscia::renderer; 

    class ECS_SpriteRenderer : public ECS_Component {
        private:
            std::reference_wrapper<Entity> _parent;

            ECS_Index<ECS_Positioned> posIndex;
            Sprite _sprite;
        public:
            void reindex(void* parent) override {
                _parent = *(Entity*)parent;
                posIndex = _parent.get().index<ECS_Positioned>();
            }

            void time_sync() override;

            ECS_SpriteRenderer(const std::string& texture_id, Entity& parent);

            void render(const Shader *shader) {
                ECS_Positioned &position = _parent.get().ref_unsafe(posIndex);
                _sprite.render(shader, position.get_pos());
            }

            /*
            void render() {
                _sprite.render();
            }

            void render(const Shader *shader, const Vec2f &position) const {
                _sprite.render(shader, position);
            }

            void render(const Shader *shader, const float &rotation) const {
                _sprite.render(shader, rotation);
            }

            void render(const Shader *shader, const Vec2f &position, const Vec2f &scale) const {
                _sprite.render(shader, position, scale);
            }

            void render(const Shader *shader, const Vec2f &position, const float &rotation) const {
                _sprite.render(shader, position, rotation);
            }

            void render(const Shader *shader, const Vec2f &position, const float &rotation, const Vec2f &scale) const {
                _sprite.render(shader, position, rotation, scale);
            }

            */

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
                //std::cout << _components.size() << "\n";
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