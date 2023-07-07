/**
 * @file 
 * grandpa.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _GRANDPA_H_
#define _GRANDPA_H_

#include "ecs_components.h"
#include "entity.h"

namespace omniscia::core {
    using namespace omni::types;
    
    /**
     * @brief Grandpa - prototype class used 
     * for creating grandpa entity instance
    */
    class Grandpa : public Entity {
        private:

        public:
            /** @brief Default Grandpa constructor */
            Grandpa(const Vec2f& position);

            /**
             * @brief Clones Grandpa entity instance
             * 
             * @return Grandpa new instance of the Grandpa object
            */
            std::shared_ptr<Entity> clone() override {
                std::shared_ptr<Grandpa> entity = std::make_shared<Grandpa>(*this);
                clone_container_to(*entity.get());
                return static_cast<std::shared_ptr<Entity>>(entity);
            }
    };
}

#endif
