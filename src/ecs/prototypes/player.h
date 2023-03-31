#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "ecs_components.h"
#include "entity.h"

namespace omniscia::core {
    class Player : public Entity {
        public:
            Player();
            Player clone();
    };
}

#endif
