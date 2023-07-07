#include "selection_tool.h"

#include "windows/level_preview_window.h"
#include "windows/tilegroups_management_window.h"

#include "systems/level_manager.h"

omniscia_editor::tools::SelectionTool::SelectionTool() {
    _startPos = Vec2f::splat(0.0f);
    _selectionColor = Vec4f(1.0f, 1.0f, 0.2f, 0.2f); 
}

void omniscia_editor::tools::SelectionTool::render_effect() {
    using namespace omniscia::core;
    using namespace omniscia_editor::systems;
    using namespace omniscia_editor::windows;
    
    const Vec2f _scroll = LevelPreviewWindow::get_instance().get_scroll();
    const Vec2f _cursorPos = LevelPreviewWindow::get_instance().get_curson_pos();
    const f32 _gridSize = LevelPreviewWindow::get_instance().get_grid_size();
    const f32 _zoom = LevelPreviewWindow::get_instance().get_zoom();
    
    ImDrawList* drawList = ImGui::GetWindowDrawList();
    
    const ImGuiIO& io = ImGui::GetIO(); 
    const ImVec2 canvasP0 = ImGui::GetCursorScreenPos();
    const Vec2f windowPos = Vec2f(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y);
    const Vec2f mousePos = Vec2f(io.MousePos.x, io.MousePos.y);

    ImVec2 canvasSZ = ImGui::GetContentRegionAvail();

    if (canvasSZ.x < 50.0f) canvasSZ.x = 50.0f;
    if (canvasSZ.y < 50.0f) canvasSZ.y = 50.0f;
    
    const Vec2f start = _scroll + windowPos;
    const Vec2f delta =  start - mousePos;  

    if(ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
        _startPos = delta / _zoom;

        const i32 selectedTileGroupIndex = TileGroupsManagementWindow::get_instance().get_selected_tile_group_index();
        LevelData& levelData = LevelManager::get_instance()._levelData;

        if(selectedTileGroupIndex <= static_cast<i32>(levelData._tileGroups.size()) - 1) {
            for(auto& tileGroup : levelData._tileGroups)
                for(auto& tile : tileGroup._tiles)
                    tile._selected = false;
        }
    }

    if(ImGui::IsMouseDown(ImGuiMouseButton_Left)) {
        drawList->AddRectFilled(
            ImVec2(start.x - _startPos.x * _zoom, start.y - _startPos.y * _zoom), 
            ImVec2(mousePos.x, mousePos.y), 
            IM_COL32(_selectionColor.x * 255, _selectionColor.y * 255, _selectionColor.z * 255, _selectionColor.w * 255)
        );
    }

    if(ImGui::IsMouseReleased(ImGuiMouseButton_Left)) {
        const i32 selectedTileGroupIndex = TileGroupsManagementWindow::get_instance().get_selected_tile_group_index();
        LevelData& levelData = LevelManager::get_instance()._levelData;

        if(selectedTileGroupIndex > static_cast<i32>(levelData._tileGroups.size()) - 1)
            return;
        
        TileGroupData& tileGroup = levelData._tileGroups[selectedTileGroupIndex];

        const Vec2f startPos = _startPos;
        const Vec2f endPos = delta / _zoom;

        for(TileEntity& tile : tileGroup._tiles) {
            const f32 minX = std::min(startPos.x, endPos.x);
            const f32 maxX = std::max(startPos.x, endPos.x);
            const f32 minY = std::min(startPos.y, endPos.y);
            const f32 maxY = std::max(startPos.y, endPos.y);

            if(tile._position.x >= minX && tile._position.x <= maxX && tile._position.y >= minY && tile._position.y <= maxY) {
                tile._selected = true;
            }
        }
    }
}

omniscia_editor::tools::SelectionTool& omniscia_editor::tools::SelectionTool::get_instance() {
    static SelectionTool tool;
    return tool;
}
