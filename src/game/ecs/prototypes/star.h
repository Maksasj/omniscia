#ifndef _STAR_H_
#define _STAR_H_

#include "ecs/ecs_components.h"
#include "ecs/entity.h"

namespace omniscia::core {
    using namespace omni::types;
    
    class Star : public Entity {
        private:

        public:
            Star(const Vec2f& position);

            std::shared_ptr<Entity> clone() override {
                std::shared_ptr<Star> entity = std::make_shared<Star>(*this);
                clone_container_to(*entity.get());
                return static_cast<std::shared_ptr<Entity>>(entity);
            }
    };
}

#endif
