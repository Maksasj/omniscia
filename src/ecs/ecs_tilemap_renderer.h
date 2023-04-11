/**
 * @file 
 * ecs_tilemap_renderer.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

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

    /**
     * @brief ECS_TilemapRenderer - component
     * that used for tilemap rendering, used with 
     * raw sprite mesh, primary used only for
     * level rendering
    */
    class ECS_TilemapRenderer : public ECS_Component {
        private:
            /**
             * @brief Pointer to the parent entity 
             * instance, used for reindexing and time sync 
            */
            Entity* _parent;
            
            u32 _layer;

            /** @brief ECS_Index of the sprite flip component */
            ECS_Index<ECS_SpriteFlip> _spriteFlipIndex;
            
            /** @brief ECS_Index of the positioned component */
            ECS_Index<ECS_Positioned> _posIndex;

            /** @brief ECS_Index of the scale component */
            ECS_Index<ECS_Scaled> _scaleIndex;

            /** @brief Sprite instance */
            Sprite _sprite;
            
        public:
            /**
             * @brief Method used for time 
             * synchronization of the component
             * instance, binds component to the
             * system
            */
            void time_sync() override;

            /**
             * @brief Method that reindexes all indexes
             * that are required by this component,
             * also updates pointer to the parent entity index
             * 
             * @param parent - pointer to the parent 
             * entity instance
            */
            void reindex(void* parent) override;
            
            /**
             * @brief Default constructor for ECS_TilemapRenderer
             * 
             * @param meshData raw mesh data that 
             * should be used for sprite initilization
             * (please use build in mesh data), or mesh
             * builder
             * 
             * @param textureId texture id 
             * @param layer rendering layer
             */
            ECS_TilemapRenderer(const RawMeshData& meshData, const std::string& textureId, const u32& layer);

            /**
             * @brief Get the rendering layer
             * 
             * @return rendering layer
            */
            u32 get_layer() const;

            /**
             * @brief Renders tiel map to the active frame buffer
             * 
             * @param shader that should be used for rendering 
            */
            void render(const Shader *shader);

            /**
             * @brief Method used for clonning single 
             * component instance, allocates copy of
             * the current component and returns pointer to it
             * 
             * @return pointer to the new component instance
            */
            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_TilemapRenderer>(*this));
            }

            /**
             * @brief Virtual method used for 
             * calculating byte size of the component
             * 
             * @return byte size of the component
            */
            u64 byte_size() override {
                return sizeof(ECS_TilemapRenderer) - sizeof(Sprite) + _sprite.byte_size();
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