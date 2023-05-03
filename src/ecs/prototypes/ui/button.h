#ifndef _BUTTON_H_
#define _BUTTON_H_

#include <functional>

#include "ecs_components.h"
#include "entity.h"

namespace omniscia::core {
    struct ButtonProp {
        Vec2f _pos = Vec2f{0.0f, 0.0f};
        Vec2f _scale = Vec2f{1.0f, 1.0f};

        struct _Collider {
            Vec2f _xRanges = Vec2f{1.0f, 1.0f};
            Vec2f _yRanges = Vec2f{1.0f, 1.0f};
        } _collider;

        struct _Renderer {
            std::string _texture = "";
            u32 _layer = 11;
        } _renderer;

        std::function<void(ECS_Button&)> _clickLambda = [](ECS_Button&) {};
        std::function<void(ECS_Button&)> _hoverLambda = [](ECS_Button&) {};
        std::function<void(ECS_Button&)> _unHoverLambda = [](ECS_Button&) {};
    };

    class Button : public Entity {
        private:

        public:
            Button();
            Button(const ButtonProp& prop = {});
            Button(const std::function<void(ECS_Button&)> clickLambda, const std::function<void(ECS_Button&)> hoverLambda);

            std::shared_ptr<Entity> clone() override {
                auto entity = std::make_shared<Entity>(*this);
                clone_container_to(*entity.get());
                return entity;
            }
    };
}

#endif
