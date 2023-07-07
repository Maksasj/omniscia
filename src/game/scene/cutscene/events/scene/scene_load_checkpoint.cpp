#include "scene_load_checkpoint.h"
#include "game.h"

omniscia::core::CE_SceneLoadCheckpointEvent::CE_SceneLoadCheckpointEvent() {

}

omniscia::core::CE_SceneLoadCheckpointEvent::CE_SceneLoadCheckpointEvent(const CE_SceneLoadCheckpointEvent&) {

}

void omniscia::core::CE_SceneLoadCheckpointEvent::operator=(const CE_SceneLoadCheckpointEvent&) {

}

omniscia::core::CE_SceneLoadCheckpointEvent::CE_SceneLoadCheckpointEvent(const CE_SceneLoadCheckpointProp& data) : CE_SceneLoadCheckpointProp(data), CE_Event(*(CE_Prop*)&data) {

}

void omniscia::core::CE_SceneLoadCheckpointEvent::execute() {
    Game::get_instance().load_dynamic_checkpoint();
}
