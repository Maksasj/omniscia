#include "wait_cutscene_event.h"
#include "game.h"

omniscia::core::CE_WaitCutsceneEvent::CE_WaitCutsceneEvent() {

}

omniscia::core::CE_WaitCutsceneEvent::CE_WaitCutsceneEvent(const CE_WaitCutsceneEvent&) {

}

void omniscia::core::CE_WaitCutsceneEvent::operator=(const CE_WaitCutsceneEvent&) {

}

omniscia::core::CE_WaitCutsceneEvent::CE_WaitCutsceneEvent(const CE_WaitCutsceneProp& data) : CE_WaitCutsceneProp(data), CE_Event(*(CE_Prop*)&data) {

}

void omniscia::core::CE_WaitCutsceneEvent::execute() {
    if(_lambda()) {
        done();
    } else {
        not_done();
    }
}
