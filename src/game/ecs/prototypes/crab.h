/**
 * @file 
 * crab.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _CRAB_H_
#define _CRAB_H_

#include "ecs/ecs_components.h"
#include "ecs/entity.h"

namespace omniscia::core {
    using namespace omni::types;
    
    /**
     * @brief Crab - prototype class used 
     * for creating crab entity instance
    */
    class Crab : public Entity {
        private:

        public:
            /** @brief Default Crab constructor */
            Crab(const Vec2f& position);

            /**
             * @brief Clones Crab entity instance
             * 
             * @return Crab new instance of the Crab object
            */
            std::shared_ptr<Entity> clone() override {
                std::shared_ptr<Crab> entity = std::make_shared<Crab>(*this);
                clone_container_to(*entity.get());
                return static_cast<std::shared_ptr<Entity>>(entity);
            }
    };
}

#endif
