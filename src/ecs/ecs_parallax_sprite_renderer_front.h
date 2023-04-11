/**
 * @file 
 * ecs_parallax_sprite_renderer_front.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

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

    /**
     * @brief ECS_ParallaxSpriteRendererFront - component
     * that used for parallax rendering of the sprite
     * calculates offset of the texture using lambda
     * expression
    */
    class ECS_ParallaxSpriteRendererFront : public ECS_Component {
        private:
            /** @brief Rendering layer */
            u32 _layer;

            /** @brief Sprite of the this component */
            Sprite _sprite;

            /** @brief Parallax layer offset */
            f32 _layerOffset;
            
            /**
             * @brief Lambda expression used for calculating
             * parallax layer offset 
            */
            std::function<f32(f32&)> _layerOffsetCallBack;

        public:
            /**
             * @brief Method used for time 
             * synchronization of the component
             * instance, binds component to the
             * system
            */
            void time_sync() override;

            /**
             * @brief Default constructor of the 
             * ECS_ParallaxSpriteRendererFront component
             * 
             * @param textureId id of the texture
             * @param layer rendering layer of the sprite
             * @param layerOffsetCallBack lambda expression used for calculating sprite offset
            */
            ECS_ParallaxSpriteRendererFront(const std::string& texture_id, const u32& layer, const std::function<f32(f32&)>& layerOffsetCallBack);
            
            /**
             * @brief Get the rendering layer
             * 
             * @return u32 rendering layer
            */
            u32 get_layer() const;

            /**
             * @brief Renders sprite to the active frame buffer
             * 
             * @param shader shader that should be used for rendering(uniforms)
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
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_ParallaxSpriteRendererFront>(*this));
            }

            /**
             * @brief Virtual method used for 
             * calculating byte size of the component
             * 
             * @return byte size of the component
            */
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