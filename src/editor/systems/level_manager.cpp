#include "level_manager.h"

#include "windows/history_window.h"

void omniscia_editor::systems::LevelManager::file_new() {

}

void omniscia_editor::systems::LevelManager::file_open() {
    using namespace omni::reflector::serialization;
    using json = nlohmann::json;

    ifstream file;
    file.open("assets/levels/level.json");

    const auto jsonObject = json::parse(file);

    windows::HistoryWindow::get_instance().record("Loaded level from file");
    
    _levelData = JsonSerializer::json_deserialize<LevelData>(jsonObject);

    file.close();
}

void omniscia_editor::systems::LevelManager::file_save() {
    using namespace omni::reflector::serialization;

    ofstream file;
    file.open("assets/levels/level.json");
    
    const auto jsonObject = JsonSerializer::json_serialize(_levelData);
    const auto stringRepresentation = jsonObject.dump(4);

    file << stringRepresentation;

    file.close();
}

omniscia_editor::systems::LevelManager& omniscia_editor::systems::LevelManager::get_instance() {
    static LevelManager manager;
    return manager;
}
