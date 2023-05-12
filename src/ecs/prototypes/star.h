#ifndef _STAR_H_
#define _STAR_H_

#include "ecs_components.h"
#include "entity.h"

namespace omniscia::core {
    using namespace omni::types;
    
    class Star : public Entity {
        private:

        public:
            Star(const Vec2f& position);

            std::shared_ptr<Entity> clone() override {
                auto entity = std::make_shared<Entity>(*this);
                clone_container_to(*entity.get());
                return entity;
            }
    };
}

#endif
