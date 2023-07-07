#ifndef _STATIC_ENTITY_SPRITEANIMATION_SET_ANIMATION_EVENT_CUTSCENE_EVENT_
#define _STATIC_ENTITY_SPRITEANIMATION_SET_ANIMATION_EVENT_CUTSCENE_EVENT_

#include <functional>
#include <string>

#include "camera.h"
#include "scene/cutscene/cutscene_event.h"

namespace omniscia::core {
    using namespace omni::types;
    
    struct CE_StaticEntitySpriteAnimationSetAnimationProp {
        CE_Prop _base;

        std::string _entityTmpName = "";
        std::string _animationId = "";
    };

    class CE_StaticEntitySpriteAnimationSetAnimationEvent : public CE_StaticEntitySpriteAnimationSetAnimationProp , public CE_Event {
        private:
            CE_StaticEntitySpriteAnimationSetAnimationEvent();
            CE_StaticEntitySpriteAnimationSetAnimationEvent(const CE_StaticEntitySpriteAnimationSetAnimationEvent&);
            void operator=(const CE_StaticEntitySpriteAnimationSetAnimationEvent&);

            void reset() override {
                reset_base();
            }

        public:
            CE_StaticEntitySpriteAnimationSetAnimationEvent(const CE_StaticEntitySpriteAnimationSetAnimationProp& data = CE_StaticEntitySpriteAnimationSetAnimationProp{});
            
            void execute() override;
    };
}

#endif
