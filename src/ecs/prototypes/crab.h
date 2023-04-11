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

#include "ecs_components.h"
#include "entity.h"

namespace omniscia::core {
    /**
     * @brief Crab - prototype class used 
     * for creating crab entity instance
    */
    class Crab : public Entity {
        private:

        public:
            /** @brief Default Crab constructor */
            Crab();

            /**
             * @brief Clones Crab entity instance
             * 
             * @return Crab new instance of the Crab object
            */
            Crab clone();
    };
}

#endif
