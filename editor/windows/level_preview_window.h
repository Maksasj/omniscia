#ifndef _OMNISCIA_EDITOR_LEVEL_PREVIEW_WINDOW_H_
#define _OMNISCIA_EDITOR_LEVEL_PREVIEW_WINDOW_H_

#include <iostream>
#include <string>

#include "../gfx.h"
#include "../types.h"

namespace omniscia_editor::windows {
    using namespace omni::types;

    class LevelPreviewWindow {
        private:
            f32 _zoom;
            Vec2f _scroll;

            f32 _zoomSpeed;
            f32 _maxZoom;
            f32 _minZoom;
        public:
            LevelPreviewWindow() {
                _zoom = 50.0f;
                _scroll = Vec2f::splat(0.0f);

                _zoomSpeed = 1.0f;
                _maxZoom = 500.0f;
                _minZoom = 5.0f;
            };

            void render() {
                ImGui::Begin("Level preview");

                ImGuiIO& io = ImGui::GetIO(); 

                ImVec2 canvasP0 = ImGui::GetCursorScreenPos();
                ImVec2 canvasSZ = ImGui::GetContentRegionAvail();

                if (canvasSZ.x < 50.0f) canvasSZ.x = 50.0f;
                if (canvasSZ.y < 50.0f) canvasSZ.y = 50.0f;
                
                ImVec2 canvasP1 = ImVec2(canvasP0.x + canvasSZ.x, canvasP0.y + canvasSZ.y);
                
                ImDrawList* drawList = ImGui::GetWindowDrawList();

                /** Grid */
                ImVec2 windowPos = ImGui::GetWindowPos();

                const Vec2f start = Vec2f(_scroll.x + windowPos.x, _scroll.y + windowPos.y);
                
                /* Axes */
                drawList->AddLine(ImVec2(start.x, canvasP0.y), ImVec2(start.x, canvasP1.y), IM_COL32(255, 255, 255, 255));
                drawList->AddLine(ImVec2(canvasP0.x, start.y), ImVec2(canvasP1.x, start.y), IM_COL32(255, 255, 255, 255));

                /* Grid it self */
                for(f32 x = start.x; x < canvasP1.x; x += _zoom)
                    drawList->AddLine(ImVec2(x, canvasP0.y), ImVec2(x, canvasP1.y), IM_COL32(200, 200, 200, 40));

                for(f32 x = start.x; x > canvasP0.x; x -= _zoom)
                    drawList->AddLine(ImVec2(x, canvasP0.y), ImVec2(x, canvasP1.y), IM_COL32(200, 200, 200, 40));

                for(f32 y = start.y; y < canvasP1.y; y += _zoom)
                    drawList->AddLine(ImVec2(canvasP0.x, y), ImVec2(canvasP1.x, y), IM_COL32(200, 200, 200, 40));

                for(f32 y = start.y; y > canvasP0.y; y -= _zoom)
                    drawList->AddLine(ImVec2(canvasP0.x, y), ImVec2(canvasP1.x, y), IM_COL32(200, 200, 200, 40));
                
                if(ImGui::IsMouseHoveringRect(canvasP0, canvasP1)) {
                    if(ImGui::IsMouseDragging(ImGuiMouseButton_Right, 0.0f))
                        _scroll += Vec2f(io.MouseDelta.x, io.MouseDelta.y);

                    /* Zooming with mouse wheel */
                    if(io.MouseWheel != 0.0f) {
                        const f32 oldZoom = _zoom;
                        const f32 newZoom = _zoom + io.MouseWheel * _zoomSpeed; 
                        const Vec2f delta = Vec2f(io.MousePos.x - _scroll.x, io.MousePos.y - _scroll.y);

                        if((newZoom < _maxZoom) && (newZoom > _minZoom)) 
                            _zoom = newZoom;

                        if(delta.x < 0.0f)
                            _scroll.x = io.MousePos.x + abs(delta.x)*(_zoom / oldZoom);
                        else
                            _scroll.x = io.MousePos.x - abs(delta.x)*(_zoom / oldZoom);

                        if(delta.y < 0.0f)
                            _scroll.y = io.MousePos.y + abs(delta.y)*(_zoom / oldZoom);
                        else
                            _scroll.y = io.MousePos.y - abs(delta.y)*(_zoom / oldZoom);  
                    }
                }

                ImGui::End();
            }

            static LevelPreviewWindow& get_instance() {
                static LevelPreviewWindow window;
                return window;
            }
    };
}

#endif
