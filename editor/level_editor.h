#ifndef _OMNISCIA_EDITOR_LEVEL_EDITOR_H_
#define _OMNISCIA_EDITOR_LEVEL_EDITOR_H_

#include <corecrt_math.h>

#include "level_data.h"
#include "gfx.h"

namespace omniscia_editor::level_editor {
    class LevelEditor {
        private:
            LevelData _levelData;

            bool _renderGrid;
            bool _gridSnap;
            ImVec2 _scroll;
            i32 _brushMode;

            i32 _selectedTileGroup;

            f32 GRID_STEP;
        public:
            LevelEditor() {
                _renderGrid = true;
                _gridSnap = true;

                _selectedTileGroup = 0;
                GRID_STEP = 50.0f;
            }

            inline void render_tab() {
                ImGui::ShowDemoWindow();
                
                if(ImGui::BeginTabItem("Level")) {
                    ImGuiIO& io = ImGui::GetIO(); 

                    if(ImGui::BeginChild("left pane", ImVec2(260, 0), true)) {
                        ImGui::SeparatorText("Editor");
                        ImGui::Checkbox("Render grid", &_renderGrid);
                        ImGui::Checkbox("Grid snap", &_gridSnap);
                        ImGui::SliderFloat("Zoom: ", &GRID_STEP, 5.0f, 250.0f, "%.3f");

                        ImGui::SeparatorText("Level");
                        ImGui::Text("Tile group count: %llu", _levelData.tileGroups.size());

                        ImGui::SeparatorText("Brush");
                        ImGui::RadioButton("Place", &_brushMode, 0); ImGui::SameLine();
                        ImGui::RadioButton("Erase", &_brushMode, 1);

                        ImGui::SeparatorText("Tile Groups");
                        if (ImGui::BeginListBox("##listbox 2", ImVec2(-FLT_MIN, 5 * ImGui::GetTextLineHeightWithSpacing()))) {
                            for (i32 n = 0; n < _levelData.tileGroups.size(); ++n) {
                                const bool is_selected = (_selectedTileGroup == n);
                                if(ImGui::Selectable(_levelData.tileGroups[n]._name.c_str(), is_selected))
                                    _selectedTileGroup = n;

                                if(is_selected)
                                    ImGui::SetItemDefaultFocus();
                            }
                            ImGui::EndListBox();
                        }

                        if(ImGui::Button("Add Tile Group"))
                            _levelData.tileGroups.push_back(TileGroup("Tile group #" + std::to_string(_levelData.tileGroups.size() + 1)));

                        ImGui::SameLine();
                        if(ImGui::Button("Delete Tile Group") && _levelData.tileGroups.size() > 0)
                            if(_selectedTileGroup < _levelData.tileGroups.size())
                                _levelData.tileGroups.erase(_levelData.tileGroups.begin() + _selectedTileGroup);

                        if(_selectedTileGroup < _levelData.tileGroups.size()) {
                            ImGui::SeparatorText("Selected Tile Group");

                            ImGui::Text("Tile count: %llu", _levelData.tileGroups[_selectedTileGroup].tiles.size());
                            ImGui::Text("Associated color: ");
                            ImGui::SameLine();
                            
                            static bool saved_palette_init = true;
                            static ImVec4 saved_palette[32] = {};
                            if (saved_palette_init)
                            {
                                for (i32 n = 0; n < IM_ARRAYSIZE(saved_palette); n++)
                                {
                                    ImGui::ColorConvertHSVtoRGB(n / 31.0f, 0.8f, 0.8f,
                                        saved_palette[n].x, saved_palette[n].y, saved_palette[n].z);
                                    saved_palette[n].w = 1.0f; // Alpha
                                }
                                saved_palette_init = false;
                            }

                            static bool alpha_preview = true;
                            static bool alpha_half_preview = false;
                            static bool drag_and_drop = true;
                            static bool options_menu = true;
                            static bool hdr = false;
                            ImVec4 color = _levelData.tileGroups[_selectedTileGroup]._associatedColor;
                            ImGuiColorEditFlags misc_flags = (hdr ? ImGuiColorEditFlags_HDR : 0) | (drag_and_drop ? 0 : ImGuiColorEditFlags_NoDragDrop) | (alpha_half_preview ? ImGuiColorEditFlags_AlphaPreviewHalf : (alpha_preview ? ImGuiColorEditFlags_AlphaPreview : 0)) | (options_menu ? 0 : ImGuiColorEditFlags_NoOptions);
                            static ImVec4 backup_color;

                            bool open_popup = ImGui::ColorButton("MyColor##3b", color, misc_flags);
                            ImGui::SameLine(0, ImGui::GetStyle().ItemInnerSpacing.x);
                            open_popup |= ImGui::Button("Change");
                            if (open_popup)
                            {
                                ImGui::OpenPopup("mypicker");
                                backup_color = color;
                            }

                            if (ImGui::BeginPopup("mypicker")) {
                                ImGui::Text("MY CUSTOM COLOR PICKER WITH AN AMAZING PALETTE!");
                                ImGui::Separator();
                                ImGui::ColorPicker4("##picker", (f32*)&color, misc_flags | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoSmallPreview);
                                ImGui::SameLine();

                                ImGui::BeginGroup(); // Lock X position
                                ImGui::Text("Current");
                                ImGui::ColorButton("##current", color, ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_AlphaPreviewHalf, ImVec2(60, 40));
                                ImGui::Text("Previous");
                                if (ImGui::ColorButton("##previous", backup_color, ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_AlphaPreviewHalf, ImVec2(60, 40)))
                                    color = backup_color;
                                ImGui::Separator();
                                ImGui::Text("Change");
                                for (i32 n = 0; n < IM_ARRAYSIZE(saved_palette); n++)
                                {
                                    ImGui::PushID(n);
                                    if ((n % 8) != 0)
                                        ImGui::SameLine(0.0f, ImGui::GetStyle().ItemSpacing.y);

                                    ImGuiColorEditFlags palette_button_flags = ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_NoTooltip;
                                    if (ImGui::ColorButton("##palette", saved_palette[n], palette_button_flags, ImVec2(20, 20)))
                                        color = ImVec4(saved_palette[n].x, saved_palette[n].y, saved_palette[n].z, color.w); // Preserve alpha!

                                    if (ImGui::BeginDragDropTarget())
                                    {
                                        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(IMGUI_PAYLOAD_TYPE_COLOR_3F))
                                            memcpy((f32*)&saved_palette[n], payload->Data, sizeof(f32) * 3);
                                        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(IMGUI_PAYLOAD_TYPE_COLOR_4F))
                                            memcpy((f32*)&saved_palette[n], payload->Data, sizeof(f32) * 4);
                                        ImGui::EndDragDropTarget();
                                    }

                                    ImGui::PopID();
                                }
                                ImGui::EndGroup();
                                ImGui::EndPopup();

                                _levelData.tileGroups[_selectedTileGroup]._associatedColor = color;
                            }
                        }


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
                        
                        const f32 mouse_threshold_for_pan = true ? -1.0f : 0.0f;

                        if(ImGui::IsMouseHoveringRect(canvas_p0, canvas_p1)) {
                            if (ImGui::IsMouseDragging(ImGuiMouseButton_Right, mouse_threshold_for_pan)) {
                                _scroll.x += io.MouseDelta.x;
                                _scroll.y += io.MouseDelta.y;
                            }
                            
                            if(ImGui::IsMouseClicked(ImGuiMouseButton_Left) && ImGui::IsWindowFocused()) {
                                if(_levelData.tileGroups.size() > 0) {
                                    f32 placePosX = io.MousePos.x - _scroll.x;
                                    f32 placePosY = io.MousePos.y - _scroll.y;
                                    

                                    if(_gridSnap) {
                                        placePosX -= fmodf(placePosX, GRID_STEP);
                                        placePosY -= fmodf(placePosY, GRID_STEP);
                                    }

                                    placePosX /= (GRID_STEP / 50.0);
                                    placePosY /= (GRID_STEP / 50.0);

                                    _levelData.tileGroups[_selectedTileGroup].tiles.push_back({placePosX, placePosY});
                                }
                            }
                        }

                        if (_renderGrid) {
                            for (f32 x = fmodf(_scroll.x, GRID_STEP); x < canvas_sz.x; x += GRID_STEP)
                                draw_list->AddLine(ImVec2(canvas_p0.x + x, canvas_p0.y), ImVec2(canvas_p0.x + x, canvas_p1.y), IM_COL32(200, 200, 200, 40));
                            for (f32 y = fmodf(_scroll.y, GRID_STEP); y < canvas_sz.y; y += GRID_STEP)
                                draw_list->AddLine(ImVec2(canvas_p0.x, canvas_p0.y + y), ImVec2(canvas_p1.x, canvas_p0.y + y), IM_COL32(200, 200, 200, 40));
                        }

                        for(auto& tileGroup : _levelData.tileGroups) {
                            for(auto tile : tileGroup.tiles) {
                                i32 xStart = _scroll.x;
                                i32 yStart = _scroll.y;

                                auto& color = tileGroup._associatedColor;

                                draw_list->AddRectFilled(
                                    {xStart + (f32)tile.x * (GRID_STEP / 50), yStart + (f32)tile.y * (GRID_STEP / 50)}, 
                                    {xStart + ((f32)tile.x * (GRID_STEP / 50) + GRID_STEP), yStart + ((f32)tile.y * (GRID_STEP / 50) + GRID_STEP)}, 
                                    IM_COL32(color.x * 255, color.y * 255, color.z * 255, color.w * 255));
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
                        ImGui::SetNextWindowPos({ImGui::GetWindowSize().x - 100, ImGui::GetWindowSize().y - 25});
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
