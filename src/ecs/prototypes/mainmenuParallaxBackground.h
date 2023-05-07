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

#ifndef _MAINMENU_PARALLAX_BACKGROUND_H_
#define _MAINMENU_PARALLAX_BACKGROUND_H_

#include "ecs_components.h"
#include "entity.h"

namespace omniscia::core {
    using namespace omni::types;
    
    /**
     * @brief MainMenuParallaxBackground - prototype class 
     * used for creating beach parallax background
     * entity instance
    */
    class MainMenuParallaxBackground : public Entity {
        private:

        public:
            /** @brief Default MainMenuParallaxBackground constructor */
            MainMenuParallaxBackground();
            
            /**
             * @brief Clones MainMenuParallaxBackground entity instance
             * 
             * @return MainMenuParallaxBackground new instance of the MainMenuParallaxBackground object
            */
            std::shared_ptr<Entity> clone() override {
                auto entity = std::make_shared<Entity>(*this);
                clone_container_to(*entity.get());
                return entity;
            }
    };
}

#endif
