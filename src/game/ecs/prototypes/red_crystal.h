#ifndef _RED_CRYSTAL_H_
#define _RED_CRYSTAL_H_

#include "ecs_components.h"
#include "entity.h"

namespace omniscia::core {
    using namespace omni::types;
    
    class RedCrystal : public Entity {
        private:

        public:
            RedCrystal(const Vec2f& position);

            std::shared_ptr<Entity> clone() override {
                std::shared_ptr<RedCrystal> entity = std::make_shared<RedCrystal>(*this);
                clone_container_to(*entity.get());
                return static_cast<std::shared_ptr<Entity>>(entity);
            }
    };
}

#endif
