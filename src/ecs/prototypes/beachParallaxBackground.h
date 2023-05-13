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

#ifndef _BEACH_PARALLAX_BACKGROUND_H_
#define _BEACH_PARALLAX_BACKGROUND_H_

#include "ecs_components.h"
#include "entity.h"

namespace omniscia::core {
    using namespace omni::types;
    
    /**
     * @brief BeachParallaxBackground - prototype class 
     * used for creating beach parallax background
     * entity instance
    */
    class BeachParallaxBackground : public Entity {
        private:

        public:
            /** @brief Default BeachParallaxBackground constructor */
            BeachParallaxBackground();
            
            /**
             * @brief Clones BeachParallaxBackground entity instance
             * 
             * @return BeachParallaxBackground new instance of the BeachParallaxBackground object
            */
            std::shared_ptr<Entity> clone() override {
                std::shared_ptr<BeachParallaxBackground> entity = std::make_shared<BeachParallaxBackground>(*this);
                clone_container_to(*entity.get());
                return static_cast<std::shared_ptr<Entity>>(entity);
            }
    };
}

#endif
