#ifndef _CUTSCENE_H_
#define _CUTSCENE_H_

#include <list>
#include <memory>

#include "cutscene_step.h"
#include "cutscene_event.h"

namespace omniscia::core {
    using namespace omni::types;
    
    class Cutscene {
        protected:
            bool _started;
            bool _ended;

            CutsceneDataPoolType _cutsceneDataPool;

            std::list<CE_Step> _steps;
            std::list<CE_Step>::iterator _currentStep;

            Cutscene();
            Cutscene(const Cutscene&);
        public:
            Cutscene(const std::initializer_list<CE_StepObject> &steps);
            void free();
            void start();
            bool is_ended() const;
            virtual void update();
    };

    bool ended_cutscene_predicate(Cutscene const* cutscene);

    struct Predicate_CutsceneEnd {
        bool operator()(Cutscene const* cutscene) {
            if(cutscene == nullptr) return true;

            return cutscene->is_ended(); 
        }
    };
}

#endif