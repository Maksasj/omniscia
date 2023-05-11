/**
 * @file 
 * player.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "ecs_components.h"
#include "entity.h"

namespace omniscia::core {
    using namespace omni::types;
    
    /**
     * @brief Player - prototype class used 
     * for creating player entity instance
    */
    class Player : public Entity {
        private:

        public:
            /** @brief Default Player constructor */
            Player(const Vec2f& position);

            /**
             * @brief Clones Player entity instance
             * 
             * @return Player new instance of the Player object
            */
            std::shared_ptr<Entity> clone() override {
                auto entity = std::make_shared<Entity>(*this);
                //clone_container_to(*entity.get());
                return entity;
            }
    };
}

#endif
