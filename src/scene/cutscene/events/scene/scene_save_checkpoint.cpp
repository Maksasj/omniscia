#include "scene_save_checkpoint.h"
#include "game.h"

omniscia::core::CE_SceneSaveCheckpointEvent::CE_SceneSaveCheckpointEvent() {

}

omniscia::core::CE_SceneSaveCheckpointEvent::CE_SceneSaveCheckpointEvent(const CE_SceneSaveCheckpointEvent&) {

}

void omniscia::core::CE_SceneSaveCheckpointEvent::operator=(const CE_SceneSaveCheckpointEvent&) {

}

omniscia::core::CE_SceneSaveCheckpointEvent::CE_SceneSaveCheckpointEvent(const CE_SceneSaveCheckpointProp& data) : CE_SceneSaveCheckpointProp(data), CE_Event(*(CE_Prop*)&data) {

}

void omniscia::core::CE_SceneSaveCheckpointEvent::execute() {
    Game::get_instance().save_dynamic_checkpoint();
}
