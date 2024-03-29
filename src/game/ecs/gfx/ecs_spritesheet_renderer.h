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

#include "ecs/gfx/ecs_sprite_animation.h"
#include "ecs/gfx/ecs_pro_renderer.h"
#include "ecs/ecs_component.tpp"
#include "ecs/gfx/ecs_sprite_flip.h"
#include "ecs/motion/ecs_positioned.h"
#include "ecs/ecs_system.h"
#include "ecs/motion/ecs_scaled.h"
#include "controls.h"
#include "ecs/entity.h"
#include "gfx/sprite.h"
#include "gfx/shader.h"

namespace omniscia::core::ecs {
    using namespace omni::types;
    using namespace omniscia::gfx; 
    using namespace omniscia::gfx::sprite;

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

            ECS_Index<ECS_Transparency> _transparencyIndex;

        public:
            friend class omni::reflector::FieldFriendlyScope;
            friend class omni::reflector::Reflection<ECS_SpriteSheetRenderer>;

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

            void _type_query(void* query) override {
                DebugFieldQuery::debug_component_edit_query<ECS_SpriteSheetRenderer>(*this);
            }
    };
}

OMNI_ADAPT_STRUCTURE_NAME(omniscia::core::ecs, ECS_SpriteSheetRenderer, _enabled, _layer);

#endif