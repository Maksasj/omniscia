#ifndef _OMNISCIA_EDITOR_LEVEL_EDITOR_H_
#define _OMNISCIA_EDITOR_LEVEL_EDITOR_H_

#include <corecrt_math.h>

#include "level_data.h"
#include "gfx.h"

namespace omniscia_editor::level_editor {
    class LevelEditor {
        private:
            LevelData<500, 500> _levelData;

            bool _renderGrid;
            ImVec2 _scroll;
            i32 _brushMode;
        public:
            LevelEditor() {
                _renderGrid = true;   
            }

            inline void render_tab() {
                if(ImGui::BeginTabItem("Level")) {
                    ImGuiIO& io = ImGui::GetIO(); 
                    
                    if(ImGui::BeginChild("left pane", ImVec2(150, 0), true)) {
                        ImGui::SeparatorText("Editor");
                        ImGui::Checkbox("Render grid", &_renderGrid);

                        ImGui::SeparatorText("Level");
                        ImGui::Text("Width: %llu", _levelData._levelWidth);
                        ImGui::Text("Height: %llu", _levelData._levelHeight);

                        ImGui::SeparatorText("Brush");
                        ImGui::RadioButton("Place", &_brushMode, 0); ImGui::SameLine();
                        ImGui::RadioButton("Erase", &_brushMode, 1);
                        
                        ImGui::EndChild();
                    }

                    ImGui::SameLine();

                    if(ImGui::BeginChild("right pane", ImVec2(0, 0), true)){
                        ImVec2 canvas_p0 = ImGui::GetCursorScreenPos();      // ImDrawList API uses screen coordinates!
                        ImVec2 canvas_sz = ImGui::GetContentRegionAvail();   // Resize canvas to what's available
                        if (canvas_sz.x < 50.0f) canvas_sz.x = 50.0f;
                        if (canvas_sz.y < 50.0f) canvas_sz.y = 50.0f;
                        ImVec2 canvas_p1 = ImVec2(canvas_p0.x + canvas_sz.x, canvas_p0.y + canvas_sz.y);

                        ImDrawList* draw_list = ImGui::GetWindowDrawList();
                        draw_list->PushClipRect(canvas_p0, canvas_p1, true);
                        draw_list->AddRectFilled(canvas_p0, canvas_p1, IM_COL32(25, 25, 25, 255));
                        
                        const float mouse_threshold_for_pan = true ? -1.0f : 0.0f;
                        if (true && ImGui::IsMouseDragging(ImGuiMouseButton_Right, mouse_threshold_for_pan)) {
                            _scroll.x += io.MouseDelta.x;
                            _scroll.y += io.MouseDelta.y;
                        }

                        if (_renderGrid) {
                            const float GRID_STEP = 64.0f;
                            for (float x = fmodf(_scroll.x, GRID_STEP); x < canvas_sz.x; x += GRID_STEP)
                                draw_list->AddLine(ImVec2(canvas_p0.x + x, canvas_p0.y), ImVec2(canvas_p0.x + x, canvas_p1.y), IM_COL32(200, 200, 200, 40));
                            for (float y = fmodf(_scroll.y, GRID_STEP); y < canvas_sz.y; y += GRID_STEP)
                                draw_list->AddLine(ImVec2(canvas_p0.x, canvas_p0.y + y), ImVec2(canvas_p1.x, canvas_p0.y + y), IM_COL32(200, 200, 200, 40));
                        }

                        for(int x = 0; x < _levelData._levelWidth; ++x) {
                            for(int y = 0; y < _levelData._levelHeight; ++y) {
                                if(!_levelData._tiles[y][x]) continue;
        
                                int xStart = _scroll.x;
                                int yStart = _scroll.y;
        
                                draw_list->AddRectFilled({xStart + (float)x*50, yStart + (float)y*50}, {xStart + ((float)x + 1)*50, yStart + ((float)y + 1)*50}, IM_COL32(255, 255, 0, 255));
                            }
                        }

                        draw_list->PopClipRect();

                        ImGuiStyle& style = ImGui::GetStyle();
                        style.WindowBorderSize = 0.0f;

                        auto flags = 
                            ImGuiWindowFlags_NoTitleBar |
                            ImGuiWindowFlags_NoMove |
                            ImGuiWindowFlags_NoSavedSettings |
                            ImGuiWindowFlags_NoDecoration |
                            ImGuiWindowFlags_NoResize;

                        ImGui::SetNextWindowBgAlpha(0.0f); // Transparent background
                        ImGui::SetNextWindowPos({ImGui::GetWindowSize().x - 190, ImGui::GetWindowSize().y - 25});
                        if (ImGui::Begin("Example: Simple overlay", NULL, flags)) {
                            ImGui::Text("Application average %.3f [ms/frame] (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
                            if (ImGui::IsMousePosValid())
                                ImGui::Text("Mouse Position: (%.1f,%.1f)", io.MousePos.x, io.MousePos.y);
                            else
                                ImGui::Text("Mouse Position: <invalid>");
                            ImGui::End();
                        }

                        ImGui::EndChild();
                    }

                    ImGui::EndTabItem();
                }
            }
    };
}

#endif
