#ifndef _ANIMATED_BACKGROUND_H_
#define _ANIMATED_BACKGROUND_H_

#include "ecs/ecs_components.h"
#include "ecs/entity.h"

namespace omniscia::core {
    using namespace omni::types;
    
    struct AnimatedBackgroundProp {
        std::string _texture = "";
        std::string _animation = "";
        u32 _layer = 0;
    };

    class AnimatedBackground : public Entity {
        private:

        public:
            AnimatedBackground();

            AnimatedBackground(const AnimatedBackgroundProp& prop = {});
            
            std::shared_ptr<Entity> clone() override {
                std::shared_ptr<AnimatedBackground> entity = std::make_shared<AnimatedBackground>(*this);
                clone_container_to(*entity.get());
                return static_cast<std::shared_ptr<Entity>>(entity);
            }
    };
}

#endif
