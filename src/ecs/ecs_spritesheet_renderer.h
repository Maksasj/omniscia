/**
 * @file 
 * ecs_spritesheet_renderer.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _ECS_SPRITESHEET_RENDERER_H_
#define _ECS_SPRITESHEET_RENDERER_H_

#include <array>
#include <memory>
#include <iostream>

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
     * @brief ECS_SpriteSheetRenderer - component that 
     * used for sprite sheet rendering, also can be used
     * for sprite sheet animation rendering
    */
    class ECS_SpriteSheetRenderer : public ECS_Component {
        private:
            /**
             * @brief Pointer to the parent entity 
             * instance, used for reindexing and time sync 
            */
            Entity* _parent;
            
            /**
             * @brief Rendering layer
            */
            u32 _layer;

            /**
             * @brief Sprite instance
            */
            Sprite _sprite;

            /** @brief ECS_Index of the sprite flip component */
            ECS_Index<ECS_SpriteFlip> _spriteFlipIndex;
            
            /** @brief ECS_Index of the sprite animation component */
            ECS_Index<ECS_SpriteAnimation> _animationIndex;
            
            /** @brief ECS_Index of the positioned component */
            ECS_Index<ECS_Positioned> _posIndex;
            
            /** @brief ECS_Index of the scale component */
            ECS_Index<ECS_Scaled> _scaleIndex;

        public:
            /* Some evil macros */
            OMNISCIA_STRING_REPRESENTATION(ECS_SpriteSheetRenderer, this->_parent << " " << this->_layer); 
            OMNISCIA_OFSTREAM_REPRESENTATION(ECS_SpriteSheetRenderer, self._parent << " " << self._layer);

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
             * @brief Default constructor of the ECS_SpriteSheetRenderer component
             * 
             * @param textureId texture id
             * @param layer rendering layer
             */
            ECS_SpriteSheetRenderer(const std::string& textureId, const u32& layer);

            /**
             * @brief Get the rendering layer
             * 
             * @return u32 rendering layer
            */
            u32 get_layer() const;

            /**
             * @brief Renders sprite sheet to the active frame buffer
             * 
             * @param shader that should be used for rendering 
            */
            void render();

            /**
             * @brief Method used for clonning single 
             * component instance, allocates copy of
             * the current component and returns pointer to it
             * 
             * @return pointer to the new component instance
            */
            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_SpriteSheetRenderer>(*this));
            }

            /**
             * @brief Virtual method used for 
             * calculating byte size of the component
             * 
             * @return byte size of the component
            */
            u64 byte_size() override {
                return sizeof(ECS_SpriteSheetRenderer) - sizeof(Sprite) + _sprite.byte_size();
            }
    };

    /**
     * @brief ECS_SpriteSheetRendererSystem - System 
     * class used for managing all updates and data for
     * all active ECS_SpriteSheetRenderer type components
    */
    class ECS_SpriteSheetRendererSystem : public ECS_System<ECS_SpriteSheetRenderer> {
        private:
            /**
             * @brief Hidden default constructor
            */
            ECS_SpriteSheetRendererSystem() : ECS_System<ECS_SpriteSheetRenderer>() {};
            
            /**
             * @brief Hidden default copy constructor
            */
            ECS_SpriteSheetRendererSystem(ECS_SpriteSheetRendererSystem const&) {};
            
            /**
             * @brief Hidden default assignment operator
            */
            void operator=(ECS_SpriteSheetRendererSystem const&) {};

        public:
            /**
             * @brief Main rendering method, renders 
             * all currently assigned components
            */
            void render() {
                if(!_enabled)
                    return;

                for(ECS_SpriteSheetRenderer* comp : _components) {
                    comp->render();
                }
            }

            /**
             * @brief Get the singleton instance of the ECS_SpriteSheetRendererSystem system
             * 
             * @return Reference to singleton instance of the ECS_SpriteSheetRendererSystem system
            */
            static ECS_SpriteSheetRendererSystem& get_instance() {
                static ECS_SpriteSheetRendererSystem instance;
                return instance;
            }
    };
}

#endif