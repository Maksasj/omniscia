#ifndef _ECS_TILEMAP_RENDERER_H_
#define _ECS_TILEMAP_RENDERER_H_

#include <array>
#include <memory>
#include <iostream>

#include "raw_mesh_data_builder.h"
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

    class ECS_TilemapRenderer : public ECS_Component {
        private:
            Entity* _parent;
            
            u32 _layer;

            ECS_Index<ECS_SpriteFlip> _spriteFlipIndex;
            ECS_Index<ECS_Positioned> _posIndex;
            ECS_Index<ECS_Scaled> _scaleIndex;

            Sprite _sprite;
        public:
            void reindex(void* parent) override;
            void time_sync() override;
            
            ECS_TilemapRenderer(const RawMeshData& meshData, const std::string& texture_id, const u32& layer);

            u32 get_layer() const;

            void render(const Shader *shader);

            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_TilemapRenderer>(*this));
            }
    };

    class ECS_TilemapRendererSystem : public ECS_System<ECS_TilemapRenderer> {
        private:
            ECS_TilemapRendererSystem() {};
            ECS_TilemapRendererSystem(ECS_TilemapRendererSystem const&) {};
            void operator=(ECS_TilemapRendererSystem const&) {};
        public:
            void render(Shader* shader) {
                for(ECS_TilemapRenderer* comp : _components) {
                    comp->render(shader);
                }
            }

            static ECS_TilemapRendererSystem& get_instance() {
                static ECS_TilemapRendererSystem instance;
                return instance;
            }
    };
}

#endif