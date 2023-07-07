#include "move_tool.h"

#include "windows/level_preview_window.h"
#include "windows/tilegroups_management_window.h"

#include "systems/level_manager.h"

omniscia_editor::tools::MoveTool::MoveTool() {
    _gridSnaping = true;

    _movedPosition = Vec2f::splat(0.0f);
}

void omniscia_editor::tools::MoveTool::render_effect() {
    using namespace omniscia::core;
    using namespace omniscia_editor::systems;
    using namespace omniscia_editor::windows;

    const Vec2f _scroll = LevelPreviewWindow::get_instance().get_scroll();
    const Vec2f _cursorPos = LevelPreviewWindow::get_instance().get_curson_pos();
    const f32 _gridSize = LevelPreviewWindow::get_instance().get_grid_size();
    const f32 _zoom = LevelPreviewWindow::get_instance().get_zoom();

    ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeAll);

    const ImGuiIO& io = ImGui::GetIO(); 

    const ImVec2 canvasP0 = ImGui::GetCursorScreenPos();
    ImVec2 canvasSZ = ImGui::GetContentRegionAvail();

    if (canvasSZ.x < 50.0f) canvasSZ.x = 50.0f;
    if (canvasSZ.y < 50.0f) canvasSZ.y = 50.0f;
    
    const ImVec2 canvasP1 = ImVec2(canvasP0.x + canvasSZ.x, canvasP0.y + canvasSZ.y);

    if(!ImGui::IsMouseHoveringRect(canvasP0, canvasP1)) {
        _movedPosition = Vec2f::splat(0.0f);
        return;
    }

    if(!ImGui::IsMouseDragging(ImGuiMouseButton_Left, 0.0f)) {
        _movedPosition = Vec2f::splat(0.0f);
        return;
    }

    const i32 selectedTileGroupIndex = TileGroupsManagementWindow::get_instance().get_selected_tile_group_index();
    LevelData& levelData = LevelManager::get_instance()._levelData;

    if(selectedTileGroupIndex > static_cast<i32>(levelData._tileGroups.size()) - 1) {
        _movedPosition = Vec2f::splat(0.0f);
        return;
    }

    const Vec2f scroll = Vec2f(io.MouseDelta.x, io.MouseDelta.y);
    _movedPosition -= scroll / _zoom;

    const Vec2f delta = _movedPosition / _gridSize;  
    const Vec2f newPosition = Vec2f(round(delta.x), round(delta.y)) * _gridSize;

    for(TileGroupData& tileGroup : levelData._tileGroups) {
        for(TileEntity& tile : tileGroup._tiles) {
            if(!tile._selected)
                continue;
            
            if(_gridSnaping) {
                if(newPosition != Vec2f::splat(0.0f)) {
                    _movedPosition = Vec2f::splat(0.0f);

                    tile._position += newPosition;
                }
            } else {
                tile._position -= scroll / _zoom;
            }
        }
    }
}

omniscia_editor::tools::MoveTool& omniscia_editor::tools::MoveTool::get_instance() {
    static MoveTool tool;
    return tool;
}
