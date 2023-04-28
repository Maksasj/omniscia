#ifndef _CUTSCENE_H_
#define _CUTSCENE_H_

#include <memory>

#include "cutscene_step.h"
#include "cutscene_event.h"

namespace omniscia::core {
    class Cutscene {
        private:
            bool _started;
            bool _ended;

            CutsceneDataPoolType _cutsceneDataPool;

            std::vector<CE_Step> _steps;
            std::vector<CE_Step>::iterator _currentStep;

            Cutscene();
            Cutscene(const Cutscene&);
        public:
            Cutscene(const std::initializer_list<CE_Step> &steps);
            void free();
            void start();
            bool is_ended() const;
            void update();
    };
}

#endif