#include "level_manager.h"

void omniscia_editor::systems::LevelManager::file_new() {

}

void omniscia_editor::systems::LevelManager::file_open() {

}

void omniscia_editor::systems::LevelManager::file_save() {
    using namespace omni::reflector::serialization;

    ofstream file;
    file.open ("level.json");
    
    const auto jsonObject = JsonSerializer::json_serialize(_levelData);
    const auto stringRepresentation = jsonObject.dump(4);

    file << stringRepresentation;

    file.close();
}

omniscia_editor::systems::LevelManager& omniscia_editor::systems::LevelManager::get_instance() {
    static LevelManager manager;
    return manager;
}
