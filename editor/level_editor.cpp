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

    ImGui::Checkbox("Render tile textures", &_renderTilesTextures);

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

void omniscia_editor::level_editor::LevelEditor::render_tile_texture_coordinate_options(TileGroup& tileGroup) {
    ImGui::Begin("Tile atlas");
        ImGui::Text("Tile atlas size: %d x %d", tileGroup._tileSetImageWidth, tileGroup._tileSetImageHeight);
        static f32 tileAtlasSize = 1.0f;

        ImVec2 canvas_p0 = ImGui::GetCursorScreenPos();
        ImVec2 canvas_sz = ImGui::GetContentRegionAvail();
        if (canvas_sz.x < 50.0f) canvas_sz.x = 50.0f;
        if (canvas_sz.y < 50.0f) canvas_sz.y = 50.0f;
        ImVec2 canvas_p1 = ImVec2(canvas_p0.x + canvas_sz.x, canvas_p0.y + canvas_sz.y);
        ImDrawList* draw_list = ImGui::GetWindowDrawList();

        draw_list->PushClipRect(canvas_p0, canvas_p1, true);
        draw_list->AddRectFilled(canvas_p0, canvas_p1, IM_COL32(25, 25, 25, 255));

        ImGui::Image(
            (void*)(intptr_t)tileGroup._tileSetTexture, 
            ImVec2( tileGroup._tileSetImageWidth * tileAtlasSize, 
                    tileGroup._tileSetImageHeight * tileAtlasSize));

        draw_list->AddRect(
            {canvas_p0.x + 0.0f, canvas_p0.y + 0.0f},
            {canvas_p0.x + tileGroup._tileSetImageWidth * tileAtlasSize, canvas_p0.y + tileGroup._tileSetImageHeight * tileAtlasSize},
            IM_COL32(200, 200, 200, 255)
        );

        draw_list->AddRect(
                {canvas_p0.x + (_brushActiveTileAtlasCordsTopLeft.x) * tileGroup._tileSetImageWidth * tileAtlasSize, 
                 canvas_p0.y + (1.0f - _brushActiveTileAtlasCordsTopLeft.y) * tileGroup._tileSetImageHeight * tileAtlasSize},

                {canvas_p0.x + (_brushActiveTileAtlasCordsBottomRight.x) * tileGroup._tileSetImageWidth * tileAtlasSize, 
                 canvas_p0.y + (1.0f - _brushActiveTileAtlasCordsBottomRight.y) * tileGroup._tileSetImageHeight * tileAtlasSize},
            IM_COL32(255, 255, 20, 255)
        );

        ImGui::Text("Tile atlas size");
        ImGui::SameLine();
        ImGui::SliderFloat("## Tile atlas size slider", &tileAtlasSize, 0.5f, 10.0f);

        ImGui::Text("Top Left");
        ImGui::InputFloat("## Brush active tile atlas texture cords top left input X", &_brushActiveTileAtlasCordsTopLeft.x, 0.05f, 0.05f, "%.3f");
        ImGui::SameLine();
        ImGui::InputFloat("## Brush active tile atlas texture cords top left input Y", &_brushActiveTileAtlasCordsTopLeft.y, 0.05f, 0.05f, "%.3f");

        ImGui::Text("Top Right");
        ImGui::InputFloat("## Brush active tile atlas texture cords top right input X", &_brushActiveTileAtlasCordsTopRight.x, 0.05f, 0.05f, "%.3f");
        ImGui::SameLine();
        ImGui::InputFloat("## Brush active tile atlas texture cords top right input Y", &_brushActiveTileAtlasCordsTopRight.y, 0.05f, 0.05f, "%.3f");

        ImGui::Text("Bottom Right");
        ImGui::InputFloat("## Brush active tile atlas texture cords bottom right input X", &_brushActiveTileAtlasCordsBottomRight.x, 0.05f, 0.05f, "%.3f");
        ImGui::SameLine();
        ImGui::InputFloat("## Brush active tile atlas texture cords bottom right input Y", &_brushActiveTileAtlasCordsBottomRight.y, 0.05f, 0.05f, "%.3f");

        ImGui::Text("Bottom Left");
        ImGui::InputFloat("## Brush active tile atlas texture cords bottom left input X", &_brushActiveTileAtlasCordsBottomLeft.x, 0.05f, 0.05f, "%.3f");
        ImGui::SameLine();
        ImGui::InputFloat("## Brush active tile atlas texture cords bottom left input Y", &_brushActiveTileAtlasCordsBottomLeft.y, 0.05f, 0.05f, "%.3f");

    ImGui::End();
}

void omniscia_editor::level_editor::LevelEditor::render_tilegroup_options() {
    ImGui::SeparatorText("Tile Groups");
    if(ImGui::BeginListBox("##tile group list box", ImVec2(-FLT_MIN, 5 * ImGui::GetTextLineHeightWithSpacing()))) {
        for (i32 n = 0; n < _levelData.tileGroups.size(); ++n) {
            const bool is_selected = (_selectedTileGroup == n);
            if(ImGui::Selectable(_levelData.tileGroups[n]._name, is_selected))
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
        auto& tileGroup = _levelData.tileGroups[_selectedTileGroup];

        if(tileGroup._tileSetLoaded) {
            render_tile_texture_coordinate_options(tileGroup);
        }

        ImGui::SeparatorText("Selected Tile Group");

        ImGui::Text("Tile count: %llu", tileGroup.tiles.size());
        ImGui::Text("Associated color: ");
        ImGui::SameLine();
        
        color_picker("Tile group color picker", tileGroup._associatedColor);

        ImGui::Text("Collision boxes");
        if(ImGui::BeginListBox("##Tile group collision box list", ImVec2(-FLT_MIN, 5 * ImGui::GetTextLineHeightWithSpacing()))) {
            for(u32 i = 0; i < tileGroup._collisionBoxes.size(); ++i) {
                auto& collisionBox = tileGroup._collisionBoxes[i];

                const bool is_selected = (_selectedCollisionBox == i);

                if(ImGui::Selectable((std::string(collisionBox._name) + "## " + std::to_string(i)).c_str(), is_selected)) 
                    _selectedCollisionBox = i;

                if(is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            
            ImGui::EndListBox();
        }

        ImGui::Text("Tile atlas");
        if(ImGui::Button("Load texture atlas")) {

            load_texture_from_file("assets/tiles/test_tiles.png", 
                &tileGroup._tileSetTexture,
                &tileGroup._tileSetImageWidth,
                &tileGroup._tileSetImageHeight);

            tileGroup._tileSetLoaded = true;            
        }

        if(ImGui::Button("Create ##Collision Box")) {
            tileGroup._collisionBoxes.push_back(CollisionBox(
                "Collision box " + std::to_string(tileGroup._collisionBoxes.size()),
                0.0f, 0.0f, omniscia::core::Vec2f{50.0f, 50.0f}, omniscia::core::Vec2f{50.0f, 50.0f}
            ));
        }


        if(_selectedCollisionBox < tileGroup._collisionBoxes.size()) {
            ImGui::SameLine();
            if(ImGui::Button("Delete ##Collision Box") && tileGroup._collisionBoxes.size() > 0) {
                tileGroup._collisionBoxes.erase(tileGroup._collisionBoxes.begin() + _selectedCollisionBox);
                _selectedCollisionBox = 0;
            }

            auto& collisionBox = tileGroup._collisionBoxes[_selectedCollisionBox];

            ImGui::SameLine();
            if(ImGui::Button("Copy ##Collision Box")) {
                tileGroup._collisionBoxes.push_back(collisionBox);

                auto& newCollisionBox = tileGroup._collisionBoxes[tileGroup._collisionBoxes.size() - 1];
                // std::string newName = newCollisionBox._name;
                // newName += " Copy";
                // newName.copy(newCollisionBox._name, min(newName.size(), 256u));
                // std::cout << newCollisionBox._name << "\n";
            }

            ImGui::SeparatorText("Collision box");
            
            ImGui::Text("Name: ");
            ImGui::SameLine();
            ImGui::InputText("##Collision Box name input label", collisionBox._name, 256);

            ImGui::Text("Associated color: ");
            ImGui::SameLine();
            color_picker("Collision box color picker", collisionBox._associatedColor);


            ImGui::Text("Possition");
            ImGui::Text("X ");
            ImGui::SameLine();
            ImGui::InputFloat("## Collision box X", &collisionBox._x, 5.0f, 5.0f, "%.3f");
            
            ImGui::Text("Y ");
            ImGui::SameLine();
            ImGui::InputFloat("## Collision box Y", &collisionBox._y, 5.0f, 5.0f, "%.3f");

            ImGui::Text("Size");
            ImGui::Text("Left ");
            ImGui::SameLine();
            ImGui::InputFloat("## Collision width X1", &collisionBox._rangesX.x, 5.0f, 5.0f, "%.3f");
            ImGui::Text("Right");
            ImGui::SameLine();
            ImGui::InputFloat("## Collision width X2", &collisionBox._rangesX.y, 5.0f, 5.0f, "%.3f");
            ImGui::Text("Up   ");
            ImGui::SameLine();
            ImGui::InputFloat("## Collision width Y1", &collisionBox._rangesY.x, 5.0f, 5.0f, "%.3f");
            ImGui::Text("Down ");
            ImGui::SameLine();
            ImGui::InputFloat("## Collision width Y2", &collisionBox._rangesY.y, 5.0f, 5.0f, "%.3f");
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
    _renderTilesTextures = false;

    _gridSnap = true;
    _gridSize = 50.0f;
    _gridSizeMin = 5.0f;
    _gridSizeMax = 500.0f;

    _selectedTileGroup = 0;
    _selectedCollisionBox = 0;
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

    _brushActiveTileAtlasCordsTopRight =    {0.125f, 1.0f}; // {1.0f, 1.0f};
    _brushActiveTileAtlasCordsBottomRight = {0.125f, 0.875f}; // {1.0f, 0.0f};
    _brushActiveTileAtlasCordsBottomLeft =  {0.0f, 0.875f}; // {0.0f, 0.0f};
    _brushActiveTileAtlasCordsTopLeft =     {0.0f, 1.0f}; // {0.0f, 1.0f};
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

            if(_renderTilesTextures) {
                if(tileGroup._tileSetLoaded) { 
                    drawList->AddImageQuad(
                        (void*)(intptr_t)tileGroup._tileSetTexture, 
                        {firstPointX, firstPointY}, 
                        {secondPointX, firstPointY},
                        {secondPointX, secondPointY},
                        {firstPointX, secondPointY}, 
                        
                        {(tile.textureCordsTopLeft.x),      (1.0f - tile.textureCordsTopLeft.y)},           //  Top Left
                        {(tile.textureCordsTopRight.x),     (1.0f - tile.textureCordsTopRight.y)},          //  Top Right
                        {(tile.textureCordsBottomRight.x),  (1.0f - tile.textureCordsBottomRight.y)},       //  Bottom Right
                        {(tile.textureCordsBottomLeft.x),   (1.0f - tile.textureCordsBottomLeft.y)});       //  Bottom Left
                }
            } else {
                drawList->AddRectFilled({firstPointX, firstPointY}, {secondPointX, secondPointY}, 
                    IM_COL32(color.x * 255, color.y * 255, color.z * 255, color.w * 255));
            }
        }
    }
}

void omniscia_editor::level_editor::LevelEditor::render_collision_boxes(ImDrawList* drawList, const ImVec2& canvas_p0, const ImVec2& canvas_p1) {
    for(auto& tileGroup : _levelData.tileGroups) {
        for(auto collisionBox : tileGroup._collisionBoxes) {
            auto& color = collisionBox._associatedColor;

            f32 factor = (_zoom / _gridSize);

            f32 firstPointX = _scroll.x + factor * ((f32)collisionBox._x - collisionBox._rangesX.x);
            f32 firstPointY = _scroll.y + factor * ((f32)collisionBox._y - collisionBox._rangesY.x);

            f32 secondPointX = _scroll.x + factor * ((f32)collisionBox._x + collisionBox._rangesX.y);
            f32 secondPointY = _scroll.y + factor * ((f32)collisionBox._y + collisionBox._rangesY.y);

            drawList->AddRect({firstPointX, firstPointY}, {secondPointX, secondPointY}, 
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
    ImGui::ShowDemoWindow();

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

            if(importButtonClicked & 1) {
                std::cout << "Importing map assets\\level.bin \n";

                _levelData.load_from_file("assets\\level.bin", get_properties());

                importButtonClicked = 0;
            }

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
                                    Tile tile = (Tile){
                                        .x = placePosX,
                                        .y = placePosY,

                                        ._width = _brushTileWidth,
                                        ._height = _brushTileWidth,

                                        .textureCordsTopRight =     _brushActiveTileAtlasCordsTopRight,
                                        .textureCordsBottomRight =  _brushActiveTileAtlasCordsBottomRight,
                                        .textureCordsBottomLeft =   _brushActiveTileAtlasCordsBottomLeft,
                                        .textureCordsTopLeft =      _brushActiveTileAtlasCordsTopLeft,
                                    };

                                    _levelData.tileGroups[_selectedTileGroup].tiles.push_back(tile);
                                } else {
                                    f32 radius = _gridSize * (_brushSize / 2);

                                    for(f32 x = placePosX - radius; x < placePosX + radius; x += _gridSize) {
                                        for(f32 y = placePosY - radius; y < placePosY + radius; y += _gridSize) {
                                            Tile tile = (Tile){
                                                .x = x,
                                                .y = y,

                                                ._width = _brushTileWidth,
                                                ._height = _brushTileWidth,

                                                .textureCordsTopRight =     _brushActiveTileAtlasCordsTopRight,
                                                .textureCordsBottomRight =  _brushActiveTileAtlasCordsBottomRight,
                                                .textureCordsBottomLeft =   _brushActiveTileAtlasCordsBottomLeft,
                                                .textureCordsTopLeft =      _brushActiveTileAtlasCordsTopLeft,
                                            };
                                            
                                            if(_brushType == 0) {
                                                if((placePosX - x)*(placePosX - x) + (placePosY - y)*(placePosY - y) > radius*radius) continue;
                                                
                                                _levelData.tileGroups[_selectedTileGroup].tiles.push_back(tile);

                                            } else if(_brushType == 1) {
                                                
                                                _levelData.tileGroups[_selectedTileGroup].tiles.push_back(tile);
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
            render_collision_boxes(draw_list, canvas_p0, canvas_p1);

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
