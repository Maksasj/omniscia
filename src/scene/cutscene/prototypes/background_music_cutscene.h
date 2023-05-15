#ifndef _BACKGROUND_MUSIC_CUTSCENE_
#define _BACKGROUND_MUSIC_CUTSCENE_

#include "cutscene_step.h"
#include "cutscene_events_prototypes.h"

#include "endless_cutscene.h"

namespace omniscia::core {
    using namespace omni::types;
    
    class BackgroundMusicCutscene : public EndlessCutscene {
        public:
            BackgroundMusicCutscene();
    };
}

#endif
