#ifndef _DIALOGUE_TAB_H_
#define _DIALOGUE_TAB_H_

#include "ecs_components.h"
#include "entity.h"

namespace omniscia::core {
    using namespace omni::types;
    
    class DialogueTab : public Entity {
        private:

        public:
            DialogueTab(const Vec2f& position);

            std::shared_ptr<Entity> clone() override {
                std::shared_ptr<DialogueTab> entity = std::make_shared<DialogueTab>(*this);
                clone_container_to(*entity.get());
                return static_cast<std::shared_ptr<Entity>>(entity);
            }
    };
}

#endif
