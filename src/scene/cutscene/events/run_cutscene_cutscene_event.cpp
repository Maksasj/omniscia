#include "run_cutscene_cutscene_event.h"
#include "game.h"

omniscia::core::CE_RunCutsceneCutsceneEvent::CE_RunCutsceneCutsceneEvent() {

}

omniscia::core::CE_RunCutsceneCutsceneEvent::CE_RunCutsceneCutsceneEvent(const CE_RunCutsceneCutsceneEvent&) {

}

void omniscia::core::CE_RunCutsceneCutsceneEvent::operator=(const CE_RunCutsceneCutsceneEvent&) {

}

omniscia::core::CE_RunCutsceneCutsceneEvent::CE_RunCutsceneCutsceneEvent(const CE_RunCutsceneCutsceneProp& data) : CE_RunCutsceneCutsceneProp(data), CE_Event(*(CE_Prop*)&data) {

}

void omniscia::core::CE_RunCutsceneCutsceneEvent::execute() {
    if(_cutsceneId == "")
        return;

    Game::get_instance().start_cutscene(_cutsceneId);
}
