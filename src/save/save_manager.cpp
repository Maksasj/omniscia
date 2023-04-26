#include "save_manager.h"

omniscia::core::SaveManager::SaveManager() {
    _activeSave = nullptr;
};

omniscia::core::SaveManager::SaveManager(const SaveManager&) {

};

void omniscia::core::SaveManager::operator=(const SaveManager&) {

};

void omniscia::core::SaveManager::load_save(std::filesystem::path path) {
    static std::string corruptionMessage = "Save " + path.string() + " is corrupted";

    if(!std::filesystem::exists(path)) throw std::exception(corruptionMessage.c_str());

    std::ifstream f(path);
    json saveData = json::parse(f);

    std::shared_ptr<Save> save = std::make_shared<Save>();

    for(auto& secretData : saveData["save"]["secrets"]) {
        if(!secretData.contains("title")) 
            throw std::exception(corruptionMessage.c_str());
        
        if(!secretData.contains("description")) 
            throw std::exception(corruptionMessage.c_str());

        if(!secretData.contains("icon")) 
            throw std::exception(corruptionMessage.c_str());

        if(!secretData.contains("unlocked")) 
            throw std::exception(corruptionMessage.c_str());

        std::string _title = secretData["title"];
        std::string _description = secretData["description"];
        std::string _icon = secretData["icon"];
        bool _unlocked = secretData["unlocked"];

        save->_secrets.push_back((SecretSaveData){ _title, _description, _icon, _unlocked });
    }
    
    f.close();

    _activeSave = save;
}

omniscia::core::SaveManager& omniscia::core::SaveManager::get_instance() {
    static SaveManager saveManager;
    return saveManager;
}
