#ifndef _DIALOGUE_TAB_H_
#define _DIALOGUE_TAB_H_

#include "ecs_components.h"
#include "entity.h"

namespace omniscia::core {
    using namespace omni::types;
    
    class DialogueTab : public Entity {
        private:

        public:
            DialogueTab(const Vec2f& pos);

            std::shared_ptr<Entity> clone() override {
                auto entity = std::make_shared<Entity>(*this);
                clone_container_to(*entity.get());
                return entity;
            }
    };
}

#endif
