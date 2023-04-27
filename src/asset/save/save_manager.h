#ifndef _SAVE_MANAGER_H_
#define _SAVE_MANAGER_H_

#include <unordered_map>
#include <fstream>

#include "save_asset.h"
#include "save_loader.h"
#include "manager.h"

namespace omniscia::core {
    class SaveManager : Manager<SaveAsset> {
        private:
            SaveManager();
            SaveManager(const SaveManager&);
            void operator=(const SaveManager&);

            std::shared_ptr<SaveAsset> _activeSave;

        public:
            void load_save(std::filesystem::path path);
            
            static SaveManager& get_instance();
    };
}

#endif