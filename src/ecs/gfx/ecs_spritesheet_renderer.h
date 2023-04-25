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
#include "ecs_pro_renderer.h"
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
    class ECS_SpriteSheetRenderer : public ECS_ProRenderer {
        private:
            /**
             * @brief Pointer to the parent entity 
             * instance, used for reindexing and time sync 
            */
            Entity* _parent;

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
             * @brief Renders sprite sheet to the active frame buffer
             * 
             * @param shader that should be used for rendering 
            */
            void render() override;

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
}

#endif