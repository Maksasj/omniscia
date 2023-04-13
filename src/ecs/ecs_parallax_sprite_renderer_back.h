/**
 * @file 
 * ecs_parallax_sprite_renderer_back.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

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

    /**
     * @brief ECS_ParallaxSpriteRendererBack - component
     * that used for parallax rendering of the sprite
     * calculates offset of the texture using lambda
     * expression
    */
    class ECS_ParallaxSpriteRendererBack : public ECS_Component {
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
            /* Some evil macros */
            OMNISCIA_STRING_REPRESENTATION(ECS_ParallaxSpriteRendererBack, this->_layer << " " << this->_layerOffset);
            OMNISCIA_OFSTREAM_REPRESENTATION(ECS_ParallaxSpriteRendererBack, self._layer << " " << self._layerOffset);

            /**
             * @brief Method used for time 
             * synchronization of the component
             * instance, binds component to the
             * system
            */
            void time_sync() override;

            /**
             * @brief Default constructor of the 
             * ECS_ParallaxSpriteRendererBack component
             * 
             * @param textureId id of the texture
             * @param layer rendering layer of the sprite
             * @param layerOffsetCallBack lambda expression used for calculating sprite offset
            */
            ECS_ParallaxSpriteRendererBack(const std::string& textureId, const u32& layer, const std::function<f32(f32&)>& layerOffsetCallBack);
            
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
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_ParallaxSpriteRendererBack>(*this));
            }

            /**
             * @brief Virtual method used for 
             * calculating byte size of the component
             * 
             * @return byte size of the component
            */
            u64 byte_size() override {
                return sizeof(ECS_ParallaxSpriteRendererBack);
            }
    };

    /**
     * @brief ECS_ParallaxSpriteRendererBackSystem - System 
     * class used for managing all updates and data for
     * all active ECS_ParallaxSpriteRendererBack type components
    */
    class ECS_ParallaxSpriteRendererBackSystem : public ECS_System<ECS_ParallaxSpriteRendererBack> {
        private:
            /**
             * @brief Hidden default constructor
            */
            ECS_ParallaxSpriteRendererBackSystem() : ECS_System<ECS_ParallaxSpriteRendererBack>() {};
            
            /**
             * @brief Hidden default copy constructor
            */
            ECS_ParallaxSpriteRendererBackSystem(ECS_ParallaxSpriteRendererBackSystem const&) {};
            
            /**
             * @brief Hidden default assignment operator
            */
            void operator=(ECS_ParallaxSpriteRendererBackSystem const&) {};

        public:
            /**
             * @brief Main rendering method, renders 
             * all currently assigned components
            */
            void render(const Shader* shader) {
                if(!_enabled)
                    return;

                for(ECS_ParallaxSpriteRendererBack* comp : _components) {
                    comp->render(shader);
                }
            }

            /**
             * @brief Get the singleton instance of the ECS_ParallaxSpriteRendererBackSystem system
             * 
             * @return Reference to singleton instance of the ECS_ParallaxSpriteRendererBackSystem system
            */
            static ECS_ParallaxSpriteRendererBackSystem& get_instance() {
                static ECS_ParallaxSpriteRendererBackSystem instance;
                return instance;
            }
    };
}

#endif