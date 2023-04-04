#include "level_editor.h"

void omniscia_editor::level_editor::LevelEditor::render_editor_options(GLFWwindow* window) {
    ImGui::SeparatorText("Editor");
    
    ImGui::Checkbox("Render grid", &_renderGrid);
    if(_renderGrid) {
        ImGui::SameLine();                          
        ImGui::Checkbox("Render axis", &_renderAxis); 
    }

    ImGui::Checkbox("Grid snap", &_gridSnap);
    if(!_gridSnap) {
        ImGui::Text("Interaction radius");
        ImGui::SliderFloat("##Interaction radius slider ", &_interactionRadius, _interactionRadiusMin, _interactionRadiusMax, "%.3f");
    } else {
        ImGui::SameLine();
    }

    ImGui::Checkbox("Player Screen box", &_renderPlayerCameraBox);

    if(ImGui::Button("Align center")) {
        i32 width;
        i32 height;
        glfwGetWindowSize(window, &width, &height);
        _scroll.x = width / 2.0;
        _scroll.y = height / 2.0;
    }

    ImGui::Text("Zoom");
    ImGui::SliderFloat("##Zoom: ", &_zoom, _minZoom, _maxZoom, "%.3f");
    
    ImGui::Text("Grid size");
    ImGui::SliderFloat("##Grid size: ", &_gridSize, _gridSizeMin, _gridSizeMax, "%.3f");
    ImGui::SameLine();
    if(ImGui::Button("Default")) {
        _gridSize = 50.0f;
    }
}

void omniscia_editor::level_editor::LevelEditor::render_level_options() {
    ImGui::SeparatorText("Level");
    ImGui::Text("Tile group count: %llu", _levelData.tileGroups.size());
}

void omniscia_editor::level_editor::LevelEditor::render_tilegroup_options() {
    ImGui::SeparatorText("Tile Groups");
    if (ImGui::BeginListBox("##tile group list box", ImVec2(-FLT_MIN, 5 * ImGui::GetTextLineHeightWithSpacing()))) {
        for (i32 n = 0; n < _levelData.tileGroups.size(); ++n) {
            const bool is_selected = (_selectedTileGroup == n);
            if(ImGui::Selectable(_levelData.tileGroups[n]._name.c_str(), is_selected))
                _selectedTileGroup = n;

            if(is_selected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndListBox();
    }

    if(ImGui::Button("Add Tile Group")) {
        _levelData.tileGroups.push_back(TileGroup("Tile group #" + std::to_string(_levelData.tileGroups.size() + 1)));
        _selectedTileGroup = _levelData.tileGroups.size() - 1;
    }

    ImGui::SameLine();
    if(ImGui::Button("Delete Tile Group") && _levelData.tileGroups.size() > 0)
        if(_selectedTileGroup < _levelData.tileGroups.size())
            _levelData.tileGroups.erase(_levelData.tileGroups.begin() + _selectedTileGroup);

    if(_selectedTileGroup < _levelData.tileGroups.size()) {
        ImGui::SeparatorText("Selected Tile Group");

        ImGui::Text("Tile count: %llu", _levelData.tileGroups[_selectedTileGroup].tiles.size());
        ImGui::Text("Associated color: ");
        ImGui::SameLine();
        
        {   /* Color picker */
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
                ImGui::Text("Color Picker");
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
    }
}

void omniscia_editor::level_editor::LevelEditor::render_brush_options() {
    ImGui::SeparatorText("Brush");
    ImGui::RadioButton("Place", &_brushMode, 0); 
    ImGui::SameLine();
    ImGui::RadioButton("Erase", &_brushMode, 1);
    ImGui::Checkbox("Continuous", &_brushContinuous);

    if(_brushMode == 0) {
        ImGui::SameLine();
        ImGui::Checkbox("Tile perfect", &_brushModeTilePerfect);

        if(!_brushModeTilePerfect) {
            ImGui::Text("Brush type");
            ImGui::RadioButton("Circle", &_brushType, 0); 
            ImGui::SameLine();
            ImGui::RadioButton("Square", &_brushType, 1);

            ImGui::Text("Brush size");
            ImGui::SameLine();
            ImGui::SliderInt("##Brush size slider ", &_brushSize, _brushSizeMin, _brushSizeMax);
        } else {
            ImGui::Text("Tile size");
            ImGui::Text("Width  ");
            ImGui::SameLine();
            ImGui::SliderFloat("## Tile width: ", &_brushTileWidth, _brushTileWidthMin, _brushTileWidthMax, "%.3f");
            ImGui::Text("Height ");
            ImGui::SameLine();
            ImGui::SliderFloat("## Tile height: ", &_brushTileHeight, _brushTileHeightMin, _brushTileHeightMax, "%.3f");
        
            if(ImGui::Button("Set default size")) {
                _brushTileWidth = _brushTileDefaultWidth;
                _brushTileHeight = _brushTileDefaultHeight;
            }
        }
    }
}

omniscia_editor::level_editor::LevelEditor::LevelEditor() {
    _renderGrid = true;
    _renderAxis = true;

    _gridSnap = true;
    _gridSize = 50.0f;
    _gridSizeMin = 5.0f;
    _gridSizeMax = 500.0f;

    _selectedTileGroup = 0;
    _interactionRadius = 10.0f;
    _interactionRadiusMin = 1.0f;
    _interactionRadiusMax = 500.0f;

    _brushModeTilePerfect = true;
    _brushContinuous = false;

    _minZoom = 5.0f;
    _maxZoom = 250.0f;
    _zoomSpeed = 1.0f;
    _zoom = 50.0f;

    _brushSize = 1;
    _brushSizeMax = 100;
    _brushSizeMin = 1;
    _brushType = 0;
    _brushTileWidth = 50.0f;
    _brushTileHeight = 50.0f;
    _brushTileWidthMin = 5.0f;
    _brushTileWidthMax = 250.0f;
    _brushTileHeightMin = 5.0f;
    _brushTileHeightMax = 250.0f;
    _brushTileDefaultWidth = 50.0f;
    _brushTileDefaultHeight = 50.0f;

    _playerScreenWidth = 1280;
    _playerScreenHeight = 800;

    _exportAllTileGroups = true;
    _exportOpenglCoordinateFlip = true;
}

void omniscia_editor::level_editor::LevelEditor::render_tiles(ImDrawList* drawList, const ImVec2& canvas_p0, const ImVec2& canvas_p1) {
    for(auto& tileGroup : _levelData.tileGroups) {
        for(auto tile : tileGroup.tiles) {
            i32 xStart = _scroll.x;
            i32 yStart = _scroll.y;

            auto& color = tileGroup._associatedColor;

            f32 factor = (_zoom / _gridSize);

            f32 firstPointX = xStart + (f32)tile.x * factor;
            f32 firstPointY = yStart + (f32)tile.y * factor;

            f32 secondPointX = firstPointX + factor * tile._width;
            f32 secondPointY = firstPointY + factor * tile._height;

            drawList->AddRectFilled({firstPointX, firstPointY}, {secondPointX, secondPointY}, 
                IM_COL32(color.x * 255, color.y * 255, color.z * 255, color.w * 255));
        }
    }
}

void omniscia_editor::level_editor::LevelEditor::render_grid(ImDrawList* drawList, const ImVec2& canvas_p0, const ImVec2& canvas_p1) {
    f32 startY = 0.0 + _scroll.y;
    f32 startX = 0.0 + _scroll.x;
    
    if(_renderAxis) {
        drawList->AddLine(ImVec2(startX, canvas_p0.y), ImVec2(startX, canvas_p1.y), IM_COL32(255, 255, 255, 255));
        drawList->AddLine(ImVec2(canvas_p0.x, startY), ImVec2(canvas_p1.x, startY), IM_COL32(255, 255, 255, 255));
    }

    for(f32 x = startX; x < canvas_p1.x; x += _zoom) {
        drawList->AddLine(ImVec2(x, canvas_p0.y), ImVec2(x, canvas_p1.y), IM_COL32(200, 200, 200, 40));
    }

    for(f32 x = startX; x > canvas_p0.x; x -= _zoom) {
        drawList->AddLine(ImVec2(x, canvas_p0.y), ImVec2(x, canvas_p1.y), IM_COL32(200, 200, 200, 40));
    }

    for(f32 y = startY; y < canvas_p1.y; y += _zoom) {
        drawList->AddLine(ImVec2(canvas_p0.x, y), ImVec2(canvas_p1.x, y), IM_COL32(200, 200, 200, 40));
    }

    for(f32 y = startY; y > canvas_p0.y; y -= _zoom) {
        drawList->AddLine(ImVec2(canvas_p0.x, y), ImVec2(canvas_p1.x, y), IM_COL32(200, 200, 200, 40));
    }
}

void omniscia_editor::level_editor::LevelEditor::render_camera_box(ImDrawList* drawList, const ImVec2& canvas_p0, const ImVec2& canvas_p1) {
    f32 radiusX = _playerScreenWidth / 2.0; 
    f32 radiusY = _playerScreenHeight / 2.0; 

    radiusX *= (_zoom / _gridSize);
    radiusY *= (_zoom / _gridSize);

    ImVec2 firstPoint = ImVec2{ _scroll.x - radiusX, _scroll.y - radiusY };
    ImVec2 secondPoint = ImVec2{ _scroll.x + radiusX, _scroll.y + radiusY };

    ImVec2 uvFirstPoint = ImVec2{ _scroll.x - radiusY, _scroll.y - radiusY };
    ImVec2 uvSecondPoint = ImVec2{ _scroll.x + radiusY, _scroll.y + radiusY };

    drawList->AddRect(uvFirstPoint, uvSecondPoint, IM_COL32(255, 255, 0, 120));
    drawList->AddRect(firstPoint, secondPoint, IM_COL32(255, 255, 0, 255));
}

void omniscia_editor::level_editor::LevelEditor::render_metrics_window() {
    ImGuiIO& io = ImGui::GetIO(); 

    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowBorderSize = 0.0f;

    auto flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize;

    ImGui::SetNextWindowBgAlpha(0.0f);
    ImGui::SetNextWindowPos({ImGui::GetWindowSize().x - 100, ImGui::GetWindowSize().y - 25});
    if (ImGui::Begin("Example: Simple overlay", NULL, flags)) {
        ImGui::Text("Application average %.3f [ms/frame] (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        if (ImGui::IsMousePosValid())
            ImGui::Text("Mouse Position: (%.1f,%.1f)", io.MousePos.x, io.MousePos.y);
        else
            ImGui::Text("Mouse Position: <invalid>");
        ImGui::End();
    }
}

void omniscia_editor::level_editor::LevelEditor::render_tab(GLFWwindow *window) {
    if(ImGui::BeginTabItem("Level")) {
        ImGuiIO& io = ImGui::GetIO(); 

        if(ImGui::BeginChild("left pane", ImVec2(260, 0), true)) {
            ImGui::SeparatorText("File");

            static i32 importButtonClicked = 0;
            if (ImGui::Button("Import level"))
                importButtonClicked++;

            ImGui::SameLine();                       
            static i32 exportButtonClicked = 0;
            if (ImGui::Button("Export level"))
                exportButtonClicked++;

            if(exportButtonClicked & 1) {
                bool tmp = true;
                ImGui::Begin("Export level");
                    ImGui::SeparatorText("Path");

                    const u64 _pathStringMaxSize = 256; 
                    static char buf1[_pathStringMaxSize] = "C:\\level.bin"; 
                    ImGui::InputText("## Export path", buf1, _pathStringMaxSize);
                    ImGui::SameLine();
                    
                    static i32 fileBrowserOpen = 0;
                    if(ImGui::Button("Browse"))
                        fileBrowserOpen++;
                    
                    if(fileBrowserOpen & 1) {
                        auto p = omniscia_editor::editor::FileExplorer::get_instance().render();
                        if(p._selected == true) {
                            using namespace editor;

                            if(p._type == _FILE) {
                                p._path.copy(buf1, p._path.size());
                            } else if(p._type == _DIRECTORY) {
                                std::string newPath = p._path + "\\level.bin";
                                newPath.copy(buf1, newPath.size());
                            }
                            fileBrowserOpen = 0;

                        }
                    }

                    ImGui::SameLine();
                    if(ImGui::Button("Export")) {
                        _levelData.export_to_file(std::string(buf1), get_properties());
                    }

                    ImGui::SeparatorText("Tile groups");
                    ImGui::Text("Tile group count %llu", _levelData.tileGroups.size());

                    u64 tileCount = 0;
                    for(const auto& tileGroup : _levelData.tileGroups) {
                        tileCount += tileGroup.tiles.size();
                    }

                    ImGui::Text("Total tile count %llu", tileCount);
                    ImGui::Checkbox("Export all tile groups ", &_exportAllTileGroups);
                    ImGui::SameLine();
                    ImGui::TextColored(ImVec4{1.0, 1.0, 1.0, 0.5}, " Recommended");

                    ImGui::SeparatorText("Generall");
                    ImGui::Checkbox("Opengl coordinates flip ", &_exportOpenglCoordinateFlip);
                    ImGui::SameLine();
                    ImGui::TextColored(ImVec4{1.0, 1.0, 1.0, 0.5}, " Recommended");

                    // ImGui::Checkbox("UV coordinates scaling ", &tmp);
                    // ImGui::SameLine();
                    // ImGui::TextColored(ImVec4{1.0, 1.0, 1.0, 0.5}, " Recommended");
                ImGui::End();
            }

            render_editor_options(window);

            render_level_options();

            render_brush_options();

            render_tilegroup_options();

            ImGui::EndChild();
        }

        ImGui::SameLine();

        if(ImGui::BeginChild("right pane", ImVec2(0, 0), true)){
            ImVec2 canvas_p0 = ImGui::GetCursorScreenPos();
            ImVec2 canvas_sz = ImGui::GetContentRegionAvail();
            if (canvas_sz.x < 50.0f) canvas_sz.x = 50.0f;
            if (canvas_sz.y < 50.0f) canvas_sz.y = 50.0f;
            ImVec2 canvas_p1 = ImVec2(canvas_p0.x + canvas_sz.x, canvas_p0.y + canvas_sz.y);

            ImDrawList* draw_list = ImGui::GetWindowDrawList();

            draw_list->PushClipRect(canvas_p0, canvas_p1, true);
            draw_list->AddRectFilled(canvas_p0, canvas_p1, IM_COL32(25, 25, 25, 255));
            
            const f32 mouse_threshold_for_pan = true ? -1.0f : 0.0f;

            if(ImGui::IsMouseHoveringRect(canvas_p0, canvas_p1)) {
                if(ImGui::IsMouseDragging(ImGuiMouseButton_Right, mouse_threshold_for_pan)) {
                    _scroll.x += io.MouseDelta.x;
                    _scroll.y += io.MouseDelta.y;
                }

                /* Zooming with mouse wheel */
                if(io.MouseWheel != 0) {
                    f32 oldZoom = _zoom;

                    if(_zoom + io.MouseWheel * _zoomSpeed > _maxZoom) 
                        _zoom = _maxZoom;
                    else 
                        _zoom += io.MouseWheel * _zoomSpeed;

                    if(_zoom + io.MouseWheel * _zoomSpeed < _minZoom) 
                        _zoom = _minZoom;
                    else
                        _zoom += io.MouseWheel * _zoomSpeed;

                    f32 deltaX = io.MousePos.x - _scroll.x;
                    f32 deltaY = io.MousePos.y - _scroll.y;

                    if(deltaX < 0)
                        _scroll.x = io.MousePos.x + abs(deltaX)*(_zoom / oldZoom);
                    else
                        _scroll.x = io.MousePos.x - abs(deltaX)*(_zoom / oldZoom);

                    if(deltaY < 0)
                        _scroll.y = io.MousePos.y + abs(deltaY)*(_zoom / oldZoom);
                    else
                        _scroll.y = io.MousePos.y - abs(deltaY)*(_zoom / oldZoom);  
                }
                
                if((ImGui::IsMouseClicked(ImGuiMouseButton_Left) || ImGui::IsMouseDown(ImGuiMouseButton_Left)) 
                    && ImGui::IsWindowFocused()) {
                    if(_levelData.tileGroups.size() > 0) {
                        f32 placePosX = io.MousePos.x - _scroll.x;
                        f32 placePosY = io.MousePos.y - _scroll.y;

                        if(placePosX < 0) {
                            placePosX -= _zoom;
                        }

                        if(placePosY < 0) {
                            placePosY -= _zoom;
                        }

                        if(_gridSnap) {
                            placePosX -= fmodf(placePosX, _zoom);
                            placePosY -= fmodf(placePosY, _zoom);
                        }

                        placePosX /= (_zoom / _gridSize);
                        placePosY /= (_zoom / _gridSize);

                        static f32 lastPlacePosX = 0;
                        static f32 lastPlacePosY = 0;

                        bool _moved = false;

                        if(placePosX != lastPlacePosX || placePosY != lastPlacePosY) {
                            _moved = true;
                            lastPlacePosX = placePosX;
                            lastPlacePosY = placePosY;
                        }

                        if(!_brushContinuous && ImGui::IsMouseClicked(ImGuiMouseButton_Left) || _brushContinuous && _moved) {
                            if(_brushMode == 0) {
                                if(_brushModeTilePerfect) {
                                    _levelData.tileGroups[_selectedTileGroup].tiles.push_back({placePosX, placePosY, _brushTileWidth, _brushTileHeight});
                                } else {
                                    f32 radius = _gridSize * (_brushSize / 2);

                                    if(_brushType == 0) {
                                        for(f32 x = placePosX - radius; x < placePosX + radius; x += _gridSize) {
                                            for(f32 y = placePosY - radius; y < placePosY + radius; y += _gridSize) {
                                                if((placePosX - x)*(placePosX - x) + (placePosY - y)*(placePosY - y) > radius*radius) continue;

                                                _levelData.tileGroups[_selectedTileGroup].tiles.push_back({x, y, _brushTileWidth, _brushTileHeight});
                                            }
                                        }
                                    } else if(_brushType == 1) {
                                        for(f32 x = placePosX - radius; x < placePosX + radius; x += _gridSize) {
                                            for(f32 y = placePosY - radius; y < placePosY + radius; y += _gridSize) {
                                                _levelData.tileGroups[_selectedTileGroup].tiles.push_back({x, y, _brushTileWidth, _brushTileHeight});
                                            }
                                        }
                                    }
                                }
                            } else if(_brushMode == 1) {
                                for(auto& tileGroup : _levelData.tileGroups) {
                                    for(auto i = 0; i != tileGroup.tiles.size(); ++i) {
                                        auto& tile = tileGroup.tiles[i];

                                        if(_gridSnap) {
                                            if(placePosX != tile.x || placePosY != tile.y) continue;
                                        } else {
                                            if((placePosX - tile.x) * (placePosX - tile.x) + (placePosY - tile.y) * (placePosY - tile.y) > _interactionRadius*_interactionRadius) continue;
                                        }

                                        tileGroup.tiles.erase(tileGroup.tiles.begin() + i);
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
            }

            /* Render tiles */
            render_tiles(draw_list, canvas_p0, canvas_p1);

            /* Render grid */
            if (_renderGrid) {
                render_grid(draw_list, canvas_p0, canvas_p1);
            }

            /* Render player camera box */
            if(_renderPlayerCameraBox) {
                render_camera_box(draw_list, canvas_p0, canvas_p1);
            }

            draw_list->PopClipRect();

            render_metrics_window();
            
            ImGui::EndChild();
        }

        ImGui::EndTabItem();
    }
}
