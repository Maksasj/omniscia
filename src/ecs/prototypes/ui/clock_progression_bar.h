#ifndef _CLOCK_PROGRESSION_BAR_H_
#define _CLOCK_PROGRESSION_BAR_H_

#include "ecs_components.h"
#include "entity.h"

namespace omniscia::core {
    using namespace omni::types;
    
    struct ClockProgressionBarProp {
        std::string _texture = "";
        std::string _animation = "";
        u32 _layer = 11;
        Vec2f _pos = Vec2f{0.0f, 0.0f};
        Vec2f _scale = Vec2f{1.0f, 1.0f};
    };

    class ClockProgressionBar : public Entity {
        private:

        public:
            ClockProgressionBar(const ClockProgressionBarProp& prop = {});

            std::shared_ptr<Entity> clone() override {
                std::shared_ptr<ClockProgressionBar> entity = std::make_shared<ClockProgressionBar>(*this);
                clone_container_to(*entity.get());
                return static_cast<std::shared_ptr<Entity>>(entity);
            }
    };
}

#endif
