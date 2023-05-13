#ifndef _CHAPTER_END_1_CUTSCENE_CUTSCENE_
#define _CHAPTER_END_1_CUTSCENE_CUTSCENE_

#include "cutscene.h"
#include "cutscene_step.h"
#include "cutscene_events_prototypes.h"

namespace omniscia::core {
    using namespace omni::types;
    
    class Chapter1EndCutscene : public Cutscene {
        public:
            Chapter1EndCutscene(Shader* transitionStageShader);
    };
}

#endif
