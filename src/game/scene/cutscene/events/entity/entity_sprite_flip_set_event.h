#ifndef _ENTITY_SPRITEFLIP_SET_EVENT_CUTSCENE_EVENT_
#define _ENTITY_SPRITEFLIP_SET_EVENT_CUTSCENE_EVENT_

#include <functional>
#include <string>

#include "camera.h"
#include "scene/cutscene/cutscene_event.h"

namespace omniscia::core {
    using namespace omni::types;
    
    struct CE_EntitySpriteFlipSetProp {
        CE_Prop _base;

        std::string _entityTmpName = "";
        bool _horizontalFlip = false;
        bool _verticalFlip = false;
    };

    class CE_EntitySpriteFlipSetEvent : public CE_EntitySpriteFlipSetProp , public CE_Event {
        private:
            CE_EntitySpriteFlipSetEvent();
            CE_EntitySpriteFlipSetEvent(const CE_EntitySpriteFlipSetEvent&);
            void operator=(const CE_EntitySpriteFlipSetEvent&);

            void reset() override {
                reset_base();
            }

        public:
            CE_EntitySpriteFlipSetEvent(const CE_EntitySpriteFlipSetProp& data = CE_EntitySpriteFlipSetProp{});
            
            void execute() override;
    };
}

#endif
