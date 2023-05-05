#ifndef _CHECKPOINT_H_
#define _CHECKPOINT_H_

#include "ecs_components.h"
#include "entity.h"

namespace omniscia::core {
    using namespace omni::types;
    
    class Checkpoint : public Entity {
        private:

        public:
            Checkpoint();

            std::shared_ptr<Entity> clone() override {
                auto entity = std::make_shared<Entity>(*this);
                clone_container_to(*entity.get());
                return entity;
            }
    };
}

#endif
