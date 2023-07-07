#ifndef _SPAWN_DIALOGUE_SPEAKER_ICON_CUTSCENE_EVENT_
#define _SPAWN_DIALOGUE_SPEAKER_ICON_CUTSCENE_EVENT_

#include <string>
#include <functional>

#include "scene/cutscene/cutscene_event.h"
#include "scene/scene.h"
#include "camera.h"

namespace omniscia::core {
    using namespace omni::types;
    
    struct CE_SpawnDialogueSpeakerIconProp {
        CE_Prop _base;
        
        std::string _entityTmpName = "";
        std::string _speakerIconTextureId = "";
    };

    class CE_SpawnDialogueSpeakerIconEvent : public CE_SpawnDialogueSpeakerIconProp , public CE_Event {
        private:
            CE_SpawnDialogueSpeakerIconEvent();
            CE_SpawnDialogueSpeakerIconEvent(const CE_SpawnDialogueSpeakerIconEvent&);
            void operator=(const CE_SpawnDialogueSpeakerIconEvent&);

            void reset() override {
                reset_base();
            }
            
        public:
            CE_SpawnDialogueSpeakerIconEvent(const CE_SpawnDialogueSpeakerIconProp& data = CE_SpawnDialogueSpeakerIconProp{});
            
            void execute() override;
    };
}

#endif
