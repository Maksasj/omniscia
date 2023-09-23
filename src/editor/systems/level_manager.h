

#ifndef _OMNISCIA_EDITOR_LEVEL_MANAGER_H_
#define _OMNISCIA_EDITOR_LEVEL_MANAGER_H_

#include "gfx.h"
#include "types.h"

#include "tools/pencil_tool.h"
#include "tools/selection_tool.h"
#include "tools/move_tool.h"
#include "tools/collision_box_tool.h"

#include "systems/texture_manager.h"

#include "windows/history_window.h"
#include "windows/level_preview_window.h"
#include "windows/selected_tilegroup_window.h"
#include "windows/tilegroups_management_window.h"

#include "level_data.h"
 
namespace omniscia_editor::systems {
    using namespace omni::types;
    using namespace omniscia::core;

    class LevelManager {
        protected:
            LevelData _levelData;

        public:
            friend class omniscia_editor::windows::SelectedTileGroupWindow;
            friend class omniscia_editor::windows::TileGroupsManagementWindow;
            friend class omniscia_editor::windows::LevelPreviewWindow;
            friend class omniscia_editor::windows::HistoryWindow;

            friend class omniscia_editor::tools::PencilTool;
            friend class omniscia_editor::tools::SelectionTool;
            friend class omniscia_editor::tools::MoveTool;
            friend class omniscia_editor::tools::CollisionBoxTool;

            void file_new();
            void file_open();
            void file_save();

            static LevelManager& get_instance();
    };
}

#endif