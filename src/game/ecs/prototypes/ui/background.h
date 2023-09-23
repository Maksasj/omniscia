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

#include "ecs/ecs_components.h"
#include "ecs/entity.h"

namespace omniscia::core {
    using namespace omni::types;
    
    struct BackgroundProp {
        std::string _texture = "";
        u32 _layer = 0;
    };

    /**
     * @brief Background - prototype class 
     * used for creating background
     * entity instance
    */
    class Background : public Entity {
        private:

        public:
            /** @brief Default Background constructor */
            Background();

            Background(const BackgroundProp& prop = {});
            
            /**
             * @brief Clones Backgr;ound entity instance
             * 
             * @return Background new instance of the Background object
            */
            std::shared_ptr<Entity> clone() override {
                std::shared_ptr<Background> entity = std::make_shared<Background>(*this);
                clone_container_to(*entity.get());
                return static_cast<std::shared_ptr<Entity>>(entity);
            }
    };
}

#endif
