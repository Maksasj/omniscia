#ifndef _BACKGROUND_MUSIC_CUTSCENE_
#define _BACKGROUND_MUSIC_CUTSCENE_

#include "scene/cutscene/cutscene_step.h"
#include "scene/cutscene/cutscene_events_prototypes.h"

#include "scene/cutscene/endless_cutscene.h"

namespace omniscia::core {
    using namespace omni::types;
    
    class BackgroundMusicCutscene : public EndlessCutscene {
        public:
            BackgroundMusicCutscene();
    };
}

#endif
