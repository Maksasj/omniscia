#ifndef _CHECKPOINT_H_
#define _CHECKPOINT_H_

#include "ecs_components.h"
#include "entity.h"

namespace omniscia::core {
    using namespace omni::types;
    
    class Checkpoint : public Entity {
        private:

        public:
            Checkpoint(const Vec2f& position);

            std::shared_ptr<Entity> clone() override {
                std::shared_ptr<Checkpoint> entity = std::make_shared<Checkpoint>(*this);
                clone_container_to(*entity.get());
                return static_cast<std::shared_ptr<Entity>>(entity);
            }
    };
}

#endif
