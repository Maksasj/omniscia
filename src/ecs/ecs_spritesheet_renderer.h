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
            void reindex(void* parent) override {
                _parent = *(Entity*)parent;

                _animationIndex = _parent.get().index<ECS_SpriteAnimation>();
                _posIndex = _parent.get().index<ECS_Positioned>();
                _scaleIndex = _parent.get().index<ECS_Scaled>();
            }

            void time_sync() override;

            u32 get_layer() const {
                return _layer;
            }

            ECS_SpriteSheetRenderer(const std::string& texture_id, Entity& parent, const u32& layer);

            void render(const Shader *shader) {
                Vec3f position = {0.0, 0.0, 0.0};
                Vec2f scale = {1.0, 1.0};
                Vec2f spriteFrameSize = {1.0, 1.0};
                Vec2f spriteFrameOffset = {0.0, 0.0};

                if(_posIndex.is_success()) {
                    ECS_Positioned &positionComp = _parent.get().ref_unsafe(_posIndex);

                    position = positionComp.get_pos();
                }

                if(_scaleIndex.is_success()) {
                    ECS_Scaled &scaleComp = _parent.get().ref_unsafe(_scaleIndex);

                    scale = scaleComp.get_scale();
                }

                if(_animationIndex.is_success()) {
                    ECS_SpriteAnimation &animationComp = _parent.get().ref_unsafe(_animationIndex);

                    spriteFrameSize = animationComp.get_frame_size();
                    spriteFrameOffset = animationComp.get_frame_offset();
                }

                _sprite.render(shader, position, 0.0f, scale, spriteFrameSize, spriteFrameOffset);
            }

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