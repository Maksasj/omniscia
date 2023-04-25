#ifndef _CUTSCENE_H_
#define _CUTSCENE_H_

#include <memory>

#include "cutscene_step.h"
#include "cutscene_event.h"
#include "cutscene_events_prototypes.h"

namespace omniscia::core {
    class Cutscene {
        private:
            bool _started;
            bool _ended;

            std::vector<CE_Step> _steps;
            std::vector<CE_Step>::iterator _current_step;

            Cutscene() {}
            Cutscene(const Cutscene&) {}
        public:
            Cutscene(const std::initializer_list<CE_Step> &steps) : _ended(false), _started(false) {
                for(const CE_Step& step : steps)
                    _steps.push_back(step);

                _started = 0;
                _current_step = _steps.begin();
            }

            void free() {
                _steps.clear();
            }

            void start() {
                _started = true;
            }

            bool is_ended() const {
                return _ended;
            }

            void update() {
                if(!_started)
                    return;

                if(_ended)
                    return;

                if(_current_step == _steps.end()) {
                    _ended = true;
                    return;
                }

                CE_Step& currentStep = *_current_step;

                currentStep.execute();

                if(currentStep.is_done())
                    ++_current_step;
            }
    };
}

#endif