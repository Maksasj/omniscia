#ifndef _ENDLESS_CUTSCENE_H_
#define _ENDLESS_CUTSCENE_H_

#include <memory>

#include "cutscene.h"

namespace omniscia::core {
    using namespace omni::types;
    
    class EndlessCutscene : public Cutscene {
        public:
            EndlessCutscene(const std::initializer_list<CE_StepObject> &steps);
            void update() override;
    };
}

#endif