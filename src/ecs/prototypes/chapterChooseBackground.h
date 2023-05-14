#ifndef _CHAPTER_CHOOSE_BACKGROUND_PARALLAX_BACKGROUND_H_
#define _CHAPTER_CHOOSE_BACKGROUND_PARALLAX_BACKGROUND_H_

#include "ecs_components.h"
#include "entity.h"

namespace omniscia::core {
    using namespace omni::types;
    
    class ChapterChooseParallaxBackground : public Entity {
        private:

        public:
            ChapterChooseParallaxBackground();
            
            std::shared_ptr<Entity> clone() override {
                std::shared_ptr<ChapterChooseParallaxBackground> entity = std::make_shared<ChapterChooseParallaxBackground>(*this);
                clone_container_to(*entity.get());
                return static_cast<std::shared_ptr<Entity>>(entity);
            }
    };
}

#endif
