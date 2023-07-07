#ifndef _BUTTON_H_
#define _BUTTON_H_

#include <functional>

#include "ecs/ecs_components.h"
#include "ecs/entity.h"

namespace omniscia::core {
    using namespace omni::types;
    
    struct ButtonProp {
        Vec2f _pos = Vec2f{0.0f, 0.0f};
        Vec2f _scale = Vec2f{1.0f, 1.0f};

        struct _Collider {
            Vec2f _xRanges = Vec2f{1.0f, 1.0f};
            Vec2f _yRanges = Vec2f{1.0f, 1.0f};
        } _collider;

        struct _Renderer {
            std::string _texture = "";
            u32 _layer = 0;
        } _renderer;

        std::function<void(ECS_Button&)> _clickLambda = [](ECS_Button&) {};
        std::function<void(ECS_Button&)> _hoverLambda = [](ECS_Button&) {};
        std::function<void(ECS_Button&)> _unHoverLambda = [](ECS_Button&) {};
    };

    class Button : public Entity {
        private:

        public:
            Button(const Vec2f& position);
            Button(const ButtonProp& prop = {});
            Button(const Vec2f& position, const std::function<void(ECS_Button&)> clickLambda, const std::function<void(ECS_Button&)> hoverLambda);

            std::shared_ptr<Entity> clone() override {
                std::shared_ptr<Button> entity = std::make_shared<Button>(*this);
                clone_container_to(*entity.get());
                return static_cast<std::shared_ptr<Entity>>(entity);
            }
    };
}

#endif
