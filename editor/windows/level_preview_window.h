#ifndef _OMNISCIA_EDITOR_LEVEL_PREVIEW_WINDOW_H_
#define _OMNISCIA_EDITOR_LEVEL_PREVIEW_WINDOW_H_

#include <iostream>
#include <string>

#include "../gfx.h"
#include "../types.h"

#include "app_window.h"

namespace omniscia_editor::windows {
    using namespace omni::types;

    class LevelPreviewWindow : public AppWindow {
        private:
            f32 _zoom;
            Vec2f _scroll;

            /* Intermediate things */
            Vec2f _cursorPos;

            /* Properies */
            f32 _gridSize;

            f32 _zoomSpeed;
            f32 _maxZoom;
            f32 _minZoom;

            bool _renderAxis;
            bool _renderGrid;

            bool _renderScreenboxPreview;
            Vec2f _screenboxPreviewSize;
        public:
            friend class omni::reflector::FieldFriendlyScope;
            friend class omni::reflector::Reflection<LevelPreviewWindow>;
            friend class LevelPreviewHelpWindow;

            LevelPreviewWindow() {
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

            void render_window() override {
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
                        _zoom = clamp(_zoom + io.MouseWheel * _zoomSpeed, _minZoom, _maxZoom);
                        
                        const Vec2f delta = (start - Vec2f(io.MousePos.x, io.MousePos.y)) / _zoom;  

                        _scroll -= delta * (oldZoom - _zoom);
                    }
                }

                _cursorPos = (start - Vec2f(io.MousePos.x, io.MousePos.y)) / _zoom;

                ImGui::End();
            }

            void render_properties() override {
                PropertiesFieldQuery::property_window_edit_query(*this);
            }

            static LevelPreviewWindow& get_instance() {
                static LevelPreviewWindow window;
                return window;
            }
    };
}

template<>																	               
struct omni::reflector::Reflection<omniscia_editor::windows::LevelPreviewWindow> {									               
    const constexpr static std::type_info &typeInfo = typeid(omniscia_editor::windows::LevelPreviewWindow);           
    const constexpr static auto clearTypeName = "LevelPreviewWindow";
    const constexpr static auto meta = std::make_tuple(
        omni::reflector::FieldFriendlyScope::field_registration(&omniscia_editor::windows::LevelPreviewWindow::_gridSize, "Grid size"),
        omni::reflector::FieldFriendlyScope::field_registration(&omniscia_editor::windows::LevelPreviewWindow::_renderAxis, "Render axis"),
        omni::reflector::FieldFriendlyScope::field_registration(&omniscia_editor::windows::LevelPreviewWindow::_renderGrid, "Render grid"),
        omni::reflector::FieldFriendlyScope::field_registration(&omniscia_editor::windows::LevelPreviewWindow::_zoomSpeed, "Zoom zpeed"),
        omni::reflector::FieldFriendlyScope::field_registration(&omniscia_editor::windows::LevelPreviewWindow::_maxZoom, "Max zoom"),
        omni::reflector::FieldFriendlyScope::field_registration(&omniscia_editor::windows::LevelPreviewWindow::_minZoom, "Min zoom"),
        omni::reflector::FieldFriendlyScope::field_registration(&omniscia_editor::windows::LevelPreviewWindow::_renderScreenboxPreview, "Render screenbox preview"),
        omni::reflector::FieldFriendlyScope::field_registration(&omniscia_editor::windows::LevelPreviewWindow::_screenboxPreviewSize, "Screenbox preview size")
    );																		               
};

#endif
