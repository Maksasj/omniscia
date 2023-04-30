#include "save_loader.h"

omniscia::core::SaveLoader::SaveLoader() {

};

omniscia::core::SaveLoader::SaveLoader(const SaveLoader&) {

};

void omniscia::core::SaveLoader::operator=(const SaveLoader&) {

};

std::vector<std::filesystem::path> omniscia::core::SaveLoader::scan_for_saves(path const & root) const {
    std::string ext = ".json";

    std::vector<path> paths;

    if (!(exists(root) && is_directory(root))) return paths;
    
    for (auto const & entry : recursive_directory_iterator(root)) {

        if (!is_regular_file(entry)) continue;
        
        auto extension = entry.path().extension();
        
        if(extension == ext)
            paths.emplace_back(entry.path());
    }

    return paths;
}

void omniscia::core::SaveLoader::validate_saves(std::vector<std::filesystem::path>& paths) const {
    paths.erase(std::remove_if(paths.begin(), paths.end(), 
        [](const path& path) {
            if(!exists(path)) return true;
            std::ifstream f(path);

            try {
                json data = json::parse(f);

                if(data["format"]["format"] != "omniscia_save_file")
                    throw std::runtime_error("Omniscia save file, format format field not found");

                if(data["format"]["version"] > _OMNISCIA_VERSION_)
                    throw std::runtime_error("Omniscia save file, not compatible game version");

            } catch(const std::runtime_error& e) {
                std::cout << e.what() << "\n";
                std::cout << "Unable to parse " << path.string() << " save file\n";
                return true;
            }
            
            return false; 
        }), paths.end());
}

omniscia::core::SaveLoader& omniscia::core::SaveLoader::get_instance() {
    static SaveLoader saveManager;
    return saveManager;
}
