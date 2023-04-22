#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "ecs_components.h"
#include "entity.h"

namespace omniscia::core {
    class Button : public Entity {
        private:

        public:
            Button();
            Button(const std::function<void(void)> clickLambda, const std::function<void(void)> hoverLambda);

            Button clone();
    };
}

#endif
