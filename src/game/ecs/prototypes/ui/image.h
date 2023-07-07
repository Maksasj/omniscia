#ifndef _IMAGE_H_
#define _IMAGE_H_

#include "ecs/ecs_components.h"
#include "ecs/entity.h"

namespace omniscia::core {
    using namespace omni::types;
    
    struct ImageProp {
        std::string _texture = "";
        u32 _layer = 11;
        f32 _transparency = 1.0f;
        Vec2f _pos = Vec2f{0.0f, 0.0f};
        Vec2f _scale = Vec2f{1.0f, 1.0f};
    };

    class Image : public Entity {
        private:

        public:
            Image(const ImageProp& prop = {});

            std::shared_ptr<Entity> clone() override {
                std::shared_ptr<Image> entity = std::make_shared<Image>(*this);
                clone_container_to(*entity.get());
                return static_cast<std::shared_ptr<Entity>>(entity);
            }
    };
}

#endif
