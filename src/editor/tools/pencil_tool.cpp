#include "pencil_tool.h"

#include "windows/level_preview_window.h"
#include "windows/tilegroups_management_window.h"

#include "systems/level_manager.h"

omniscia_editor::tools::PencilTool::PencilTool() {
    _renderGhostTile = true;
    _ghostTileColor = Vec4f(1.0f, 1.0f, 0.2f, 0.2f); 
}

void omniscia_editor::tools::PencilTool::render_effect() {
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

    const f32 tileHalfWidth = _gridSize * 0.5f;
    const f32 tileHalfWidthScreen = tileHalfWidth * _zoom;

    const Vec2f start = _scroll + windowPos + tileHalfWidthScreen;
    const Vec2f delta =  (start - mousePos) / (_gridSize * _zoom);  
    const Vec2f deltaNew = Vec2f(round(delta.x), round(delta.y)) * _gridSize * _zoom;
    const Vec2f ghostPos = start - deltaNew;

    drawList->AddRectFilled(
        ImVec2(ghostPos.x - tileHalfWidthScreen, ghostPos.y - tileHalfWidthScreen), 
        ImVec2(ghostPos.x + tileHalfWidthScreen, ghostPos.y + tileHalfWidthScreen), 
        IM_COL32(_ghostTileColor.x * 255, _ghostTileColor.y * 255, _ghostTileColor.z * 255, _ghostTileColor.w * 255)
    );

    if(!ImGui::IsMouseClicked(ImGuiMouseButton_Left))
        return;

    const i32 selectedTileGroupIndex = TileGroupsManagementWindow::get_instance().get_selected_tile_group_index();
    LevelData& levelData = LevelManager::get_instance()._levelData;
    if(selectedTileGroupIndex > static_cast<i32>(levelData._tileGroups.size()) - 1)
        return;
    
    const Vec2f scaledCursorPos = _cursorPos / _gridSize;
    const Vec2f alignedCursorPos = Vec2f(floor(scaledCursorPos.x), floor(scaledCursorPos.y)) * _gridSize;

    levelData._tileGroups[selectedTileGroupIndex]._tiles.push_back(TileEntity{alignedCursorPos, 0});
}

omniscia_editor::tools::PencilTool& omniscia_editor::tools::PencilTool::get_instance() {
    static PencilTool tool;
    return tool;
}
