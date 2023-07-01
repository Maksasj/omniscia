#include "level_manager.h"

void omniscia_editor::systems::LevelManager::file_new() {

}

void omniscia_editor::systems::LevelManager::file_open() {

}

void omniscia_editor::systems::LevelManager::file_save() {

}

omniscia_editor::systems::LevelManager& omniscia_editor::systems::LevelManager::get_instance() {
    static LevelManager manager;
    return manager;
}
