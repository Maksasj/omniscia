#ifndef _SCENE_DIALOGUE_CUTSCENE_
#define _SCENE_DIALOGUE_CUTSCENE_

#include "cutscene_step.h"
#include "cutscene_events_prototypes.h"

namespace omniscia::core {
    using namespace omni::types;
    
    struct DialogueStepData {
        std::string _speakerIconTexture;
        i32 _side;
        std::string _text;

        DialogueStepData(const std::string& speakerIconTexture, const i32& side, const std::string& text);
    };

    class DialogueCutscene : public Cutscene {
        public:
            DialogueCutscene(Shader* transitionStageShader, const std::vector<DialogueStepData> dialogueData);
    };
}

#endif
