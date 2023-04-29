#ifndef _ENTITY_SPRITERENDERER_SET_TEXTURE_EVENT_CUTSCENE_EVENT_
#define _ENTITY_SPRITERENDERER_SET_TEXTURE_EVENT_CUTSCENE_EVENT_

#include <functional>
#include <string>

#include "camera.h"
#include "cutscene_event.h"

namespace omniscia::core {
    struct CE_EntitySpriteRendererSetTextureProp {
        CE_Prop _base;

        std::string _entityTmpName = "";
        std::string _textureId = "";
    };

    class CE_EntitySpriteRendererSetTextureEvent : public CE_EntitySpriteRendererSetTextureProp , public CE_Event {
        private:
            CE_EntitySpriteRendererSetTextureEvent();
            CE_EntitySpriteRendererSetTextureEvent(const CE_EntitySpriteRendererSetTextureEvent&);
            void operator=(const CE_EntitySpriteRendererSetTextureEvent&);

        public:
            CE_EntitySpriteRendererSetTextureEvent(const CE_EntitySpriteRendererSetTextureProp& data = CE_EntitySpriteRendererSetTextureProp{});
            
            void execute() override;
    };
}

#endif
