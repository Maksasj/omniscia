#ifndef _SAVE_LOADER_H_
#define _SAVE_LOADER_H_

#include <iostream>
#include <fstream>
#include <filesystem>

#include <nlohmann/json.hpp>

#include "version.h"
#include "save.h"

namespace omniscia::core {
    using namespace nlohmann::literals;
    using namespace std::filesystem;
    using json = nlohmann::json;
    using SaveData = json;

    class SaveLoader {
        private:
            SaveLoader();
            SaveLoader(const SaveLoader&);
            void operator=(const SaveLoader&);

        public:
            std::vector<path> scan_for_saves(path const & root) const;
            void validate_saves(std::vector<path>& paths) const;

            static SaveLoader& get_instance();
    };
}

#endif