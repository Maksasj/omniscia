

#ifndef _OMNISCIA_EDITOR_LEVEL_MANAGER_H_
#define _OMNISCIA_EDITOR_LEVEL_MANAGER_H_

#include "../gfx.h"
#include "../types.h"

#include "../windows/selected_tilegroup_window.h"
#include "../windows/tilegroups_management_window.h"

#include "level_data_ref.h"
 
namespace omniscia_editor::systems {
    using namespace omni::types;
    using namespace omniscia::core;

    class LevelManager {
        protected:
            LevelData _levelData;

        public:
            friend class omniscia_editor::windows::SelectedTileGroupWindow;
            friend class omniscia_editor::windows::TileGroupsManagementWindow;

            void file_new() {}
            void file_open() {}
            void file_save() {}

            static LevelManager& get_instance() {
                static LevelManager manager;
                return manager;
            }
    };
}

#endif