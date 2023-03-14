#ifndef _ECS_SPRITE_RENDERER_H_
#define _ECS_SPRITE_RENDERER_H_

#include <array>
#include <memory>
#include <iostream>

#include "sprite.h"
#include "shader.h"
#include "ecs_component.tpp"
#include "controls.h"

namespace omniscia::core::ecs {
    using namespace omniscia::renderer::sprite;
    using namespace omniscia::renderer; 

    class ECS_SpriteRenderer : public ECS_Component {
        private:
            Sprite _sprite;
        public:
            ECS_SpriteRenderer() : _sprite() {}
            ECS_SpriteRenderer(const std::string& texture_id) : _sprite(texture_id) {}
            
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

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_SpriteRenderer>(*this));
            }
    };
}

#endif