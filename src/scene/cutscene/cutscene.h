#ifndef _CUTSCENE_H_
#define _CUTSCENE_H_

#include <memory>

#include "cutscene_event.h"

#include "terminal_print_cutscene_event.h"
#include "stop_system_cutscene_event.h"

namespace omniscia::core {
    class Cutscene {
        private:
            bool _started;
            i32 _current_event = 0;

            std::vector<std::unique_ptr<CE_Event>> _events;

            Cutscene() {}
            Cutscene(const Cutscene&) {}
        public:
            Cutscene(const std::initializer_list<CE_Event*> &events) {
                for(CE_Event* event : events)
                    _events.push_back(std::unique_ptr<CE_Event>(event));

                _started = 0;
            }

            void start() {
                _started = true;
            }

            void update() {
                if(!_started)
                    return;

                _events[_current_event].get()->run();
                ++_current_event;
            }
            
    };
}

#endif