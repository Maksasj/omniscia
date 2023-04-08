#ifndef _CRAB_H_
#define _CRAB_H_

#include "ecs_components.h"
#include "entity.h"

namespace omniscia::core {
    class Crab : public Entity {
        public:
            Crab();
            Crab clone();
    };
}

#endif
