#ifndef _CUTSCENE_STEP_
#define _CUTSCENE_STEP_

#include <memory>
#include <string>

#include "cutscene_event.h"

namespace omniscia::core {
    class CE_Step {
        private:
            bool _is_done_executing = false;
            std::vector<std::shared_ptr<CE_Event>> _events;

        public:
            CE_Step(const CE_Event* event) {
                _events.push_back(std::shared_ptr<CE_Event>((CE_Event*)event));
            }

            CE_Step(const std::initializer_list<CE_Event*> &events) {
                for(CE_Event* event : events)
                    _events.push_back(std::shared_ptr<CE_Event>(event));
            }

            void bind_cutscene_data_pool(CutsceneDataPoolType& cutsceneDataPool) {
                for(auto event : _events) {
                    event->bind_cutscene_data_pool(cutsceneDataPool);
                }
            }

            void execute() {
                u64 eventsDone = 0;
                
                for(std::shared_ptr<CE_Event>& eventPtr : _events) {
                    CE_Event& event = *(eventPtr.get());

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
}

#endif
