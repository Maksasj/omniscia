#ifndef _BEACH_PARALLAX_BACKGROUND_H_
#define _BEACH_PARALLAX_BACKGROUND_H_

#include "ecs_components.h"
#include "entity.h"

namespace omniscia::core {
    class BeachParallaxBackground : public Entity {
        public:
            BeachParallaxBackground();
            BeachParallaxBackground clone();
    };
}

#endif
