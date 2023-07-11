#include "collision_box_tool.h"

#include "windows/level_preview_window.h"
#include "windows/tilegroups_management_window.h"

#include "systems/level_manager.h"

omniscia_editor::tools::CollisionBoxTool::CollisionBoxTool() {
    _startPos = Vec2f::splat(0.0f);
    _selectionColor = Vec4f(1.0f, 1.0f, 0.2f, 0.2f); 

    _renderFilledCollisionBoxGhost = false;
}

void omniscia_editor::tools::CollisionBoxTool::render_effect() {
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
    }

    if(ImGui::IsMouseDown(ImGuiMouseButton_Left)) {
        if(_renderFilledCollisionBoxGhost) {
            drawList->AddRectFilled(
                ImVec2(start.x - _startPos.x * _zoom, start.y - _startPos.y * _zoom), 
                ImVec2(mousePos.x, mousePos.y), 
                IM_COL32(_selectionColor.x * 255, _selectionColor.y * 255, _selectionColor.z * 255, _selectionColor.w * 255)
            );
        } else {
            drawList->AddRect(
                ImVec2(start.x - _startPos.x * _zoom, start.y - _startPos.y * _zoom), 
                ImVec2(mousePos.x, mousePos.y), 
                IM_COL32(_selectionColor.x * 255, _selectionColor.y * 255, _selectionColor.z * 255, _selectionColor.w * 255),
                0.0f,
                ImDrawFlags_None,
                2.0f
            );
        }
    }

    if(ImGui::IsMouseReleased(ImGuiMouseButton_Left)) {
        const i32 selectedTileGroupIndex = TileGroupsManagementWindow::get_instance().get_selected_tile_group_index();
        LevelData& levelData = LevelManager::get_instance()._levelData;

        if(selectedTileGroupIndex > static_cast<i32>(levelData._tileGroups.size()) - 1)
            return;
        
        TileGroupData& tileGroup = levelData._tileGroups[selectedTileGroupIndex];

        const Vec2f startPos = _startPos;
        const Vec2f endPos = delta / _zoom;

        const Vec2f& position = Vec2f(startPos.x + endPos.x, startPos.y + endPos.y) / 2.0f;
        const Vec2f& rangesX = Vec2f(position.x - startPos.x, position.x - endPos.x);
        const Vec2f& rangesY =Vec2f(position.y - startPos.y, position.y - endPos.y);

        tileGroup._collisionBoxes.push_back(
            CollisionBoxEntity("Unnamed collision box", position, rangesX, rangesY));
    }
}

omniscia_editor::tools::CollisionBoxTool& omniscia_editor::tools::CollisionBoxTool::get_instance() {
    static CollisionBoxTool tool;
    return tool;
}
