#ifndef _CUTSCENE_STEP_
#define _CUTSCENE_STEP_

#include <memory>
#include <string>
#include <functional>

#include "scene/cutscene/cutscene_event.h"

namespace omniscia::core {
    using namespace omni::types;
    
    class CE_Step {
        private:
            bool _is_done_executing = false;
            std::vector<std::shared_ptr<CE_Event>> _events;

        public:
            CE_Step(const CE_Event* event) {
                _events.push_back(std::shared_ptr<CE_Event>((CE_Event*)event));
            }

            void reset() {
                _is_done_executing = false;

                std::vector<std::shared_ptr<CE_Event>>::iterator it;
                for(it = _events.begin(); it != _events.end(); ++it) {
                    auto& e = *it; 
                    e->reset();
                }
            }

            CE_Step(const std::initializer_list<CE_Event*> &events) {
                std::initializer_list<CE_Event*>::const_iterator it;

                for(it = events.begin(); it != events.end(); ++it) {
                    const auto& event = *it;

                    _events.push_back(std::shared_ptr<CE_Event>(event));
                }
            }

            void bind_cutscene_data_pool(CutsceneDataPoolType& cutsceneDataPool) {
                std::vector<std::shared_ptr<omniscia::core::CE_Event>>::iterator it;

                for(it = _events.begin(); it != _events.end(); ++it) {
                    auto& event = *it;
                    
                    event->bind_cutscene_data_pool(cutsceneDataPool);
                }
            }

            void execute() {
                u64 eventsDone = 0;
                
                std::vector<std::shared_ptr<omniscia::core::CE_Event>>::iterator it;
                for(it = _events.begin(); it != _events.end(); ++it) {
                    CE_Event& event = **it;

                    if(event.is_done()) {
                        if(event.finishing())
                            ++eventsDone;

                        continue;
                    }

                    event.try_start();
                    if(event.is_started()) {
                        event.execute();
                        event.increment_reapet_counter();
                    }
                }

                if(eventsDone == _events.size())
                    _is_done_executing = true;
            }

            bool is_done() const {
                return _is_done_executing;
            }
    };

    struct CE_StepObject {
        std::vector<CE_Step> _steps;

        CE_StepObject() {

        }

        CE_StepObject(const CE_Step& step) {
            _steps.push_back(step);
        }
    };

    template<typename T>
    struct CE_MultiStep : public CE_StepObject {
        CE_MultiStep(const i32& count, const std::vector<T>& stepsData, const std::function<std::vector<CE_Step>(const T& stepData)> _stepLambda) {
            for(auto i = 0; i < count; ++i) {
                const std::vector<omniscia::core::CE_Step> tmpSteps = _stepLambda(stepsData[i]);

                std::vector<omniscia::core::CE_Step>::const_iterator it;
                for(it = tmpSteps.begin(); it != tmpSteps.end(); ++it) {
                    const auto& step = *it;
                    _steps.push_back(step);
                }
            }
        }
    };
}

#endif
