#ifndef _SOUND_LOOP_CUTSCENE_EVENT_
#define _SOUND_LOOP_CUTSCENE_EVENT_

#include <string>

#include "cutscene_event.h"

namespace omniscia::core {
    using namespace omni::types;
    
    struct CE_SoundLoopCutsceneProp {
        CE_Prop _base;
        std::string _soundId;
    };

    class CE_SoundLoopCutsceneEvent : public CE_SoundLoopCutsceneProp , public CE_Event {
        private:
            CE_SoundLoopCutsceneEvent();
            CE_SoundLoopCutsceneEvent(const CE_SoundLoopCutsceneEvent&);
            void operator=(const CE_SoundLoopCutsceneEvent&);

            void reset() override {
                reset_base();
            }

        public:
            CE_SoundLoopCutsceneEvent(const CE_SoundLoopCutsceneProp& data = CE_SoundLoopCutsceneProp{});
            void execute() override;
    };
}

#endif
