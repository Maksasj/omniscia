#include "scene_switch_cutscene_event.h"
#include "game.h"

omniscia::core::CE_SceneSwitchEvent::CE_SceneSwitchEvent() {

}

omniscia::core::CE_SceneSwitchEvent::CE_SceneSwitchEvent(const CE_SceneSwitchEvent&) {

}

void omniscia::core::CE_SceneSwitchEvent::operator=(const CE_SceneSwitchEvent&) {

}

omniscia::core::CE_SceneSwitchEvent::CE_SceneSwitchEvent(const CE_SceneSwitchProp& data) : CE_SceneSwitchProp(data), CE_Event(*(CE_Prop*)&data) {

}

void omniscia::core::CE_SceneSwitchEvent::execute() {
    if(_sceneName == "") return;

    Game::get_instance().switch_scene(_sceneName);

    /* Resolve this cringe */
    DebugUI::get_instance().get_metrics()._isTimeJump = true;
}
