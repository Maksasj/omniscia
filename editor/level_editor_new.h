#ifndef _OMNISCIA_EDITOR_LEVEL_EDITOR_NEW_H_
#define _OMNISCIA_EDITOR_LEVEL_EDITOR_NEW_H_

#include <corecrt_math.h>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <functional>

#include "image_loading.h"

#include "level_editor_properties.h"
#include "level/level_data.h"
#include "file_explorer/files_explorer.h"
#include "color_picker.h"
#include "gfx.h"

using namespace omni::types;

void render_grid(ImDrawList* drawList, const ImVec2& canvas_p0, const ImVec2& canvas_p1) {
    float _zoom = 50.0;

    ImVec2 _windowPos = ImGui::GetWindowPos();

    Vec2f _scroll = Vec2f(0.0 + _windowPos.x, 0.0 + _windowPos.y);

    f32 startY = 0.0 + _scroll.y;
    f32 startX = 0.0 + _scroll.x;
    
    drawList->AddLine(ImVec2(startX, canvas_p0.y), ImVec2(startX, canvas_p1.y), IM_COL32(255, 255, 255, 255));
    drawList->AddLine(ImVec2(canvas_p0.x, startY), ImVec2(canvas_p1.x, startY), IM_COL32(255, 255, 255, 255));

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

namespace omniscia_editor::level_editor {
    using namespace omni::types;

    class LevelEditor {
        private:

        public:
            void render() {
                // if(!ImGui::BeginTabItem("Level editor")) return;
                
                if(ImGui::Begin("Level preview")) {
                    ImVec2 canvas_p0 = ImGui::GetCursorScreenPos();
                    ImVec2 canvas_sz = ImGui::GetContentRegionAvail();
                    if (canvas_sz.x < 50.0f) canvas_sz.x = 50.0f;
                    if (canvas_sz.y < 50.0f) canvas_sz.y = 50.0f;
                    ImVec2 canvas_p1 = ImVec2(canvas_p0.x + canvas_sz.x, canvas_p0.y + canvas_sz.y);
                    ImDrawList* draw_list = ImGui::GetWindowDrawList();
                    
                    render_grid(draw_list, canvas_p0, canvas_p1);

                    ImGui::End();
                }
                    
                // ImGui::EndTabItem();
            }

            static LevelEditor get_instance() {
                static LevelEditor levelEditor;
                return levelEditor;
            }
    };
}

#endif
