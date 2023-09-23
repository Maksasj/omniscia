#ifndef _PLAYER_COLLECT_STAR_CUTSCENE_
#define _PLAYER_COLLECT_STAR_CUTSCENE_

#include "scene/cutscene/cutscene_step.h"
#include "scene/cutscene/cutscene_events_prototypes.h"

namespace omniscia::core {
    using namespace omni::types;
    
    class PlayerCollectStarCutscene : public Cutscene {
        public:
            PlayerCollectStarCutscene(Shader* transitionStageShader);
    };
}

#endif
