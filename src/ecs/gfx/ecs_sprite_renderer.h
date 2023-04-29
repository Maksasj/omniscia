/**
 * @file 
 * ecs_sprite_renderer.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _ECS_SPRITE_RENDERER_H_
#define _ECS_SPRITE_RENDERER_H_

#include <array>
#include <memory>
#include <iostream>

#include "ecs_pro_renderer.h"
#include "ecs_component.tpp"
#include "ecs_positioned.h"
#include "ecs_system.h"
#include "ecs_scaled.h"
#include "controls.h"
#include "entity.h"
#include "sprite.h"
#include "shader.h"
#include "ecs_sprite_flip.h"

namespace omniscia::core::ecs {
    using namespace omniscia::gfx::sprite;
    using namespace omniscia::gfx; 

    /**
     * @brief ECS_SpriteRenderer - component that 
     * used for sprite rendering, uses entity 
     * position(if exist), and entity scale(if exist)
    */
    class ECS_SpriteRenderer : public ECS_ProRenderer {
        private:
            /**
             * @brief Pointer to the parent entity 
             * instance, used for reindexing and time sync 
            */
            Entity* _parent;

            /** @brief ECS_Index of the positioned component */
            ECS_Index<ECS_Positioned> _posIndex;

            /** @brief ECS_Index of the scale component */
            ECS_Index<ECS_Scaled> _scaleIndex;
            
            ECS_Index<ECS_Transparency> _transparencyIndex;

            ECS_Index<ECS_SpriteFlip> _spriteFlipIndex;

            /**
             * @brief Sprite instance
            */
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
             * @brief Default constructor of the sprite renderer component
             * 
             * @param textureId if of the texture
             * @param layer rendering layer
             */
            ECS_SpriteRenderer(const std::string& textureId, const u32& layer);

            /**
             * @brief Renders sprite to the active frame buffer
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
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_SpriteRenderer>(*this));
            }

            /**
             * @brief Virtual method used for 
             * calculating byte size of the component
             * 
             * @return byte size of the component
            */
            u64 byte_size() override {
                return sizeof(ECS_SpriteRenderer) - sizeof(Sprite) + _sprite.byte_size();
            }
    };
}

#endif