#ifndef _CRAB_CORRUPTED_H_
#define _CRAB_CORRUPTED_H_

#include "ecs_components.h"
#include "entity.h"

namespace omniscia::core {
    using namespace omni::types;

    class CrabCorrupted : public Entity {
        private:

        public:
            CrabCorrupted(const Vec2f& position);

            std::shared_ptr<Entity> clone() override {
                std::shared_ptr<CrabCorrupted> entity = std::make_shared<CrabCorrupted>(*this);
                clone_container_to(*entity.get());
                return static_cast<std::shared_ptr<Entity>>(entity);
            }
    };
}

#endif
