/**
 * @file 
 * beachParallaxBackground.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _MENU_BACKGROUND_H_
#define _MENU_BACKGROUND_H_

#include "ecs_components.h"
#include "entity.h"

namespace omniscia::core {
    /**
     * @brief MenuBackground - prototype class 
     * used for creating beach parallax background
     * entity instance
    */
    class MenuBackground : public Entity {
        private:

        public:
            /** @brief Default MenuBackground constructor */
            MenuBackground();
            
            /**
             * @brief Clones MenuBackground entity instance
             * 
             * @return MenuBackground new instance of the MenuBackground object
            */
            std::shared_ptr<Entity> clone() override {
                auto entity = std::make_shared<Entity>(*this);
                clone_container_to(*entity.get());
                return entity;
            }
    };
}

#endif
