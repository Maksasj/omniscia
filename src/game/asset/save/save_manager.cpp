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

    if(!std::filesystem::exists(path)) throw std::runtime_error(corruptionMessage.c_str());

    std::ifstream f(path);
    json saveData = json::parse(f);

    std::shared_ptr<SaveAsset> save = std::make_shared<SaveAsset>();

    for(auto& secretData : saveData["save"]["secrets"]) {
        if(!secretData.contains("title")) 
            throw std::runtime_error(corruptionMessage.c_str());
        
        if(!secretData.contains("description")) 
            throw std::runtime_error(corruptionMessage.c_str());

        if(!secretData.contains("icon")) 
            throw std::runtime_error(corruptionMessage.c_str());

        if(!secretData.contains("unlocked")) 
            throw std::runtime_error(corruptionMessage.c_str());

        std::string title = secretData["title"];
        std::string description = secretData["description"];
        std::string icon = secretData["icon"];
        bool unlocked = secretData["unlocked"];

        save->_secrets.push_back((SecretSaveData){ title, description, icon, unlocked });
    }
    
    f.close();

    _activeSave = save;
}

omniscia::core::SaveManager& omniscia::core::SaveManager::get_instance() {
    static SaveManager saveManager;
    return saveManager;
}
