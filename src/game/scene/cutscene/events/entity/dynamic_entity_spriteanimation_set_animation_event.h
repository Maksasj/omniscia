#ifndef _DYNAMIC_ENTITY_SPRITEANIMATION_SET_ANIMATION_EVENT_CUTSCENE_EVENT_
#define _DYNAMIC_ENTITY_SPRITEANIMATION_SET_ANIMATION_EVENT_CUTSCENE_EVENT_

#include <functional>
#include <string>

#include "camera.h"
#include "cutscene_event.h"

namespace omniscia::core {
    using namespace omni::types;
    
    struct CE_DynamicEntitySpriteAnimationSetAnimationProp {
        CE_Prop _base;

        std::string _entityTmpName = "";
        std::string _animationId = "";
    };

    class CE_DynamicEntitySpriteAnimationSetAnimationEvent : public CE_DynamicEntitySpriteAnimationSetAnimationProp , public CE_Event {
        private:
            CE_DynamicEntitySpriteAnimationSetAnimationEvent();
            CE_DynamicEntitySpriteAnimationSetAnimationEvent(const CE_DynamicEntitySpriteAnimationSetAnimationEvent&);
            void operator=(const CE_DynamicEntitySpriteAnimationSetAnimationEvent&);

            void reset() override {
                reset_base();
            }

        public:
            CE_DynamicEntitySpriteAnimationSetAnimationEvent(const CE_DynamicEntitySpriteAnimationSetAnimationProp& data = CE_DynamicEntitySpriteAnimationSetAnimationProp{});
            
            void execute() override;
    };
}

#endif
