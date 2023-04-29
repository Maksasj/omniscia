#include "terminal_print_cutscene_event.h"

omniscia::core::CE_LogEvent::CE_LogEvent() {
    
}

omniscia::core::CE_LogEvent::CE_LogEvent(const CE_LogEvent&) {

}

void omniscia::core::CE_LogEvent::operator=(const CE_LogEvent&) {
    
}


omniscia::core::CE_LogEvent::CE_LogEvent(const CE_LogProp& data) : CE_LogProp(data), CE_Event(*(CE_Prop*)&data) {

}

void omniscia::core::CE_LogEvent::execute() {
    std::cout << _message << "\n";
}
