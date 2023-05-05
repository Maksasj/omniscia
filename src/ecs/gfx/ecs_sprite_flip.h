/**
 * @file 
 * ecs_sprite_flip.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _ECS_COMPONENT_SPRITE_FLIP_H_
#define _ECS_COMPONENT_SPRITE_FLIP_H_

#include <array>
#include <memory>
#include <iostream>

#include "ecs_component.tpp"
#include "controls.h"
#include "entity.h"

namespace omniscia::core::ecs {
    using namespace omni::types;
    
    /**
     * @brief ECS_SpriteFlip - component that stores
     * if sprite should be flipped, used by sprite renderers,
     * tile renderer
    */
    class ECS_SpriteFlip : public ECS_Component {
        private:
            /** @brief Is spirite flipped horizontally */
            bool _horizontalFlip;
            
            /** @brief Is spirite flipped vertically */
            bool _verticalFlip;

        public:
            /* Some evil macros */
            OMNISCIA_STRING_REPRESENTATION(ECS_SpriteFlip, this->_horizontalFlip << " " << this->_verticalFlip); 
            OMNISCIA_OFSTREAM_REPRESENTATION(ECS_SpriteFlip, self._horizontalFlip << " " << self._verticalFlip);
        
            /**
             * @brief Default constructor of the ECS_SpriteFlip component
            */
            ECS_SpriteFlip();

            /**
             * @brief Default constructor of the ECS_SpriteFlip component
             * 
             * @param horizontalFlip is sprite should be flipped horizontally
             * @param verticalFlip is sprite should be flipped vertically
             */
            ECS_SpriteFlip(const bool& horizontalFlip, const bool& verticalFlip);

            /**
             * @brief Get if sprite flipped horizontally
             * 
             * @return true sprite is flipped horizontally
             * @return false sprite is not flipped horizontally
            */
            bool get_horizontal_flip() const;

            /**
             * @brief Get if sprite flipped vertically
             * 
             * @return true sprite is flipped vertically
             * @return false sprite is not flipped vertically
            */
            bool get_vertical_flip() const;

            /**
             * @brief Sets horizontal flip of the sprite 
             * 
             * @param flip bolean represents if sprite should be flipped horizontally
            */
            void set_horizontal_flip(const bool& flip);

            /**
             * @brief Sets verticall flip of the sprite 
             * 
             * @param flip bolean represents if sprite should be flipped vertically
            */
            void set_vertical_flip(const bool& flip);

            /**
             * @brief Method used for clonning single 
             * component instance, allocates copy of
             * the current component and returns pointer to it
             * 
             * @return pointer to the new component instance
            */
            std::shared_ptr<ECS_Component> clone() override {
                return static_cast<std::shared_ptr<ECS_Component>>(std::make_shared<ECS_SpriteFlip>(*this));
            }

            /**
             * @brief Virtual method used for 
             * calculating byte size of the component
             * 
             * @return byte size of the component
            */
            u64 byte_size() override {
                return sizeof(ECS_SpriteFlip);
            }
    };
}

#endif