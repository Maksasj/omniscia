#ifndef _ANIMATED_BUTTON_H_
#define _ANIMATED_BUTTON_H_

#include <functional>

#include "ecs_components.h"
#include "entity.h"

namespace omniscia::core {
    using namespace omni::types;
    
    struct AnimatedButtonProp {
        Vec2f _pos = Vec2f{0.0f, 0.0f};
        Vec2f _scale = Vec2f{1.0f, 1.0f};

        struct _Collider {
            Vec2f _xRanges = Vec2f{1.0f, 1.0f};
            Vec2f _yRanges = Vec2f{1.0f, 1.0f};
        } _collider;

        struct _Renderer {
            std::string _texture = "";
            std::string _animation = "";
            u32 _layer = 0;
        } _renderer;

        std::function<void(ECS_Button&)> _clickLambda = [](ECS_Button&) {};
        std::function<void(ECS_Button&)> _hoverLambda = [](ECS_Button&) {};
        std::function<void(ECS_Button&)> _unHoverLambda = [](ECS_Button&) {};
    };

    class AnimatedButton : public Entity {
        private:

        public:
            AnimatedButton(const AnimatedButtonProp& prop = {});

            std::shared_ptr<Entity> clone() override {
                std::shared_ptr<AnimatedButton> entity = std::make_shared<AnimatedButton>(*this);
                clone_container_to(*entity.get());
                return static_cast<std::shared_ptr<Entity>>(entity);
            }
    };
}

#endif
