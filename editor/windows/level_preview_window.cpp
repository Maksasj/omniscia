#include "level_preview_window.h"

#include "../systems/level_manager.h"

omniscia_editor::windows::LevelPreviewWindow::LevelPreviewWindow() {
    _zoom = 1.0f;
    _scroll = Vec2f::splat(0.0f);

    _cursorPos = Vec2f::splat(0.0f);

    _gridSize = 16.0f;
    _zoomSpeed = 0.02f;
    _maxZoom = 5.0f;
    _minZoom = 0.05f;

    _renderGrid = true;
    _renderAxis = true;

    _renderScreenboxPreview = true;
    _screenboxPreviewSize = Vec2(256.0f, 144.0f);
};

omni::types::Vec2f omniscia_editor::windows::LevelPreviewWindow::get_scroll() const {
    return _scroll;
}

omni::types::f32 omniscia_editor::windows::LevelPreviewWindow::get_zoom() const {
    return _zoom;
}

omni::types::Vec2f omniscia_editor::windows::LevelPreviewWindow::get_curson_pos() const {
    return _cursorPos;
}

omni::types::f32 omniscia_editor::windows::LevelPreviewWindow::get_grid_size() const {
    return _gridSize;
}

void omniscia_editor::windows::LevelPreviewWindow::render_window() {
    using namespace omniscia::core;
    using namespace omniscia_editor::systems;

    if(!ImGui::Begin("Level preview")) {
        ImGui::End();
        return;
    }

    const ImGuiIO& io = ImGui::GetIO(); 

    const ImVec2 canvasP0 = ImGui::GetCursorScreenPos();
    ImVec2 canvasSZ = ImGui::GetContentRegionAvail();

    if (canvasSZ.x < 50.0f) canvasSZ.x = 50.0f;
    if (canvasSZ.y < 50.0f) canvasSZ.y = 50.0f;
    
    const ImVec2 canvasP1 = ImVec2(canvasP0.x + canvasSZ.x, canvasP0.y + canvasSZ.y);
    
    ImDrawList* drawList = ImGui::GetWindowDrawList();

    /** Grid */
    const ImVec2 windowPos = ImGui::GetWindowPos();

    const Vec2f start = Vec2f(_scroll.x + windowPos.x, _scroll.y + windowPos.y);
    
    /* Axes */ 
    if(_renderAxis) {
        drawList->AddLine(ImVec2(start.x, canvasP0.y), ImVec2(start.x, canvasP1.y), IM_COL32(255, 255, 255, 255));
        drawList->AddLine(ImVec2(canvasP0.x, start.y), ImVec2(canvasP1.x, start.y), IM_COL32(255, 255, 255, 255));
    }

    if(_renderScreenboxPreview)
        drawList->AddRect(
            ImVec2(start.x - (_screenboxPreviewSize.x / 2.0f) * _zoom, start.y - (_screenboxPreviewSize.y / 2.0f) * _zoom), 
            ImVec2(start.x + (_screenboxPreviewSize.x / 2.0f) * _zoom, start.y + (_screenboxPreviewSize.y / 2.0f) * _zoom), 
            IM_COL32(255, 255, 100, 255));

    /* Grid it self */
    if(_renderGrid) {
        for(f32 x = start.x; x < canvasP1.x; x += _gridSize * _zoom)
            drawList->AddLine(ImVec2(x, canvasP0.y), ImVec2(x, canvasP1.y), IM_COL32(200, 200, 200, 40));

        for(f32 x = start.x; x > canvasP0.x; x -= _gridSize * _zoom)
            drawList->AddLine(ImVec2(x, canvasP0.y), ImVec2(x, canvasP1.y), IM_COL32(200, 200, 200, 40));

        for(f32 y = start.y; y < canvasP1.y; y += _gridSize * _zoom)
            drawList->AddLine(ImVec2(canvasP0.x, y), ImVec2(canvasP1.x, y), IM_COL32(200, 200, 200, 40));

        for(f32 y = start.y; y > canvasP0.y; y -= _gridSize * _zoom)
            drawList->AddLine(ImVec2(canvasP0.x, y), ImVec2(canvasP1.x, y), IM_COL32(200, 200, 200, 40));
    }

    /* Render tiles */
    LevelData& levelData = LevelManager::get_instance()._levelData;

    for(const auto& tileGroup : levelData._tileGroups) {
        for(const auto& tile : tileGroup._tiles) {
            drawList->AddRectFilled(
                ImVec2((start.x - tile._position.x * _zoom),                        (start.y - tile._position.y * _zoom)),
                ImVec2((start.x - tile._position.x * _zoom) - _gridSize * _zoom,    (start.y - tile._position.y * _zoom) - _gridSize * _zoom),
                IM_COL32(tileGroup._tileGroupAssociatedColor.x * 255.0f, tileGroup._tileGroupAssociatedColor.y * 255.0f, tileGroup._tileGroupAssociatedColor.z * 255.0f, tileGroup._tileGroupAssociatedColor.w * 255.0f)
            );

            if(tile._selected) {
                drawList->AddRectFilled(
                    ImVec2((start.x - tile._position.x * _zoom),                        (start.y - tile._position.y * _zoom)),
                    ImVec2((start.x - tile._position.x * _zoom) - _gridSize * _zoom,    (start.y - tile._position.y * _zoom) - _gridSize * _zoom),
                    IM_COL32(255.0f, 255.0f, 51.0f, 200.0f)
                );
            }
        }
    }

    if(!ImGui::IsWindowHovered()) {
        ImGui::End();
        return;
    }

    if(ImGui::IsMouseHoveringRect(canvasP0, canvasP1)) {
        if(ImGui::IsMouseDragging(ImGuiMouseButton_Right, 0.0f))
            _scroll += Vec2f(io.MouseDelta.x, io.MouseDelta.y);

        /* Zooming with mouse wheel */
        if(io.MouseWheel != 0.0f) {
            const f32 oldZoom = _zoom;
            _zoom = omni::types::clamp(_zoom + io.MouseWheel * _zoomSpeed, _minZoom, _maxZoom);
            
            const Vec2f delta = (start - Vec2f(io.MousePos.x, io.MousePos.y)) / _zoom;  

            _scroll -= delta * (oldZoom - _zoom);
        }
    }

    _cursorPos = (start - Vec2f(io.MousePos.x, io.MousePos.y)) / _zoom;

    ToolsWindow::get_instance()._tools[ToolsWindow::get_instance().selectedToolIndex]._tool->render_effect();

    ImGui::End();
}

void omniscia_editor::windows::LevelPreviewWindow::render_properties() {
    PropertiesFieldQuery::property_window_edit_query(*this);
}

omniscia_editor::windows::LevelPreviewWindow& omniscia_editor::windows::LevelPreviewWindow::get_instance() {
    static LevelPreviewWindow window;
    return window;
}

