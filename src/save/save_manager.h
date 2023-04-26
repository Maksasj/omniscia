#ifndef _SAVE_MANAGER_H_
#define _SAVE_MANAGER_H_

#include <unordered_map>
#include <fstream>

#include "save.h"
#include "save_loader.h"

namespace omniscia::core {
    class SaveManager {
        private:
            SaveManager();
            SaveManager(const SaveManager&);
            void operator=(const SaveManager&);

            std::shared_ptr<Save> _activeSave;

        public:
            void load_save(std::filesystem::path path);
            
            static SaveManager& get_instance();
    };
}

#endif