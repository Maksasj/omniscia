#ifndef _IMAGE_H_
#define _IMAGE_H_

#include "ecs_components.h"
#include "entity.h"

namespace omniscia::core {
    struct ImageProp {
        std::string _texture = "";
        u32 _layer = 0;
        Vec2f _pos = Vec2f{0.0f, 0.0f};
        Vec2f _scale = Vec2f{1.0f, 1.0f};
    };

    class Image : public Entity {
        private:

        public:
            Image(const ImageProp& prop = {});
            
            std::shared_ptr<Entity> clone() override {
                auto entity = std::make_shared<Entity>(*this);
                clone_container_to(*entity.get());
                return entity;
            }
    };
}

#endif
