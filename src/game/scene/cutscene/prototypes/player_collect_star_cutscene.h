#ifndef _PLAYER_COLLECT_STAR_CUTSCENE_
#define _PLAYER_COLLECT_STAR_CUTSCENE_

#include "cutscene_step.h"
#include "cutscene_events_prototypes.h"

namespace omniscia::core {
    using namespace omni::types;
    
    class PlayerCollectStarCutscene : public Cutscene {
        public:
            PlayerCollectStarCutscene(Shader* transitionStageShader);
    };
}

#endif
