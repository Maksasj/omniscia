#ifndef _ENTITY_SPRITEANIMATION_SET_ANIMATION_EVENT_CUTSCENE_EVENT_
#define _ENTITY_SPRITEANIMATION_SET_ANIMATION_EVENT_CUTSCENE_EVENT_

#include <functional>
#include <string>

#include "camera.h"
#include "cutscene_event.h"

namespace omniscia::core {
    using namespace omni::types;
    
    struct CE_EntitySpriteAnimationSetAnimationProp {
        CE_Prop _base;

        std::string _entityTmpName = "";
        std::string _animationId = "";
    };

    class CE_EntitySpriteAnimationSetAnimationEvent : public CE_EntitySpriteAnimationSetAnimationProp , public CE_Event {
        private:
            CE_EntitySpriteAnimationSetAnimationEvent();
            CE_EntitySpriteAnimationSetAnimationEvent(const CE_EntitySpriteAnimationSetAnimationEvent&);
            void operator=(const CE_EntitySpriteAnimationSetAnimationEvent&);

            void reset() override {
                reset_base();
            }

        public:
            CE_EntitySpriteAnimationSetAnimationEvent(const CE_EntitySpriteAnimationSetAnimationProp& data = CE_EntitySpriteAnimationSetAnimationProp{});
            
            void execute() override;
    };
}

#endif
