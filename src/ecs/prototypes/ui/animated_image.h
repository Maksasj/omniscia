#ifndef _ANIMATED_IMAGE_H_
#define _ANIMATED_IMAGE_H_

#include "ecs_components.h"
#include "entity.h"

namespace omniscia::core {
    using namespace omni::types;
    
    struct AnimatedImageProp {
        std::string _texture = "";
        std::string _animation = "";
        u32 _layer = 11;
        Vec2f _pos = Vec2f{0.0f, 0.0f};
        Vec2f _scale = Vec2f{1.0f, 1.0f};
    };

    class AnimatedImage : public Entity {
        private:

        public:
            AnimatedImage(const AnimatedImageProp& prop = {});

            std::shared_ptr<Entity> clone() override {
                std::shared_ptr<AnimatedImage> entity = std::make_shared<AnimatedImage>(*this);
                clone_container_to(*entity.get());
                return static_cast<std::shared_ptr<Entity>>(entity);
            }
    };
}

#endif
