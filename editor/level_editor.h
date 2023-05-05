#ifndef _OMNISCIA_EDITOR_LEVEL_EDITOR_H_
#define _OMNISCIA_EDITOR_LEVEL_EDITOR_H_

#include <corecrt_math.h>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <functional>

#include "level_editor_properties.h"
#include "level/level_data.h"
#include "file_explorer/files_explorer.h"
#include "color_picker.h"
#include "gfx.h"

namespace omniscia_editor::level_editor {
    using namespace omni::types;

    class LevelEditor : public LevelEditorProperties {
        private:
            LevelData _levelData;

            void render_rect(
                ImDrawList* drawList, 
                const ImVec2& topLeft, 
                const ImVec2& topRight, 
                const ImVec2& bottomLeft, 
                const ImVec2& bottomRight,
                const ImU32& color, 
                f32 thickness);

            void render_editor_options(GLFWwindow* window);
            void render_level_options();
            void render_tile_texture_coordinate_options(TileGroup& tileGroup);
            void render_tilegroup_options();
            void render_brush_options();

            void render_tiles(ImDrawList* drawList, const ImVec2& canvas_p0, const ImVec2& canvas_p1);
            void render_collision_boxes(ImDrawList* drawList, const ImVec2& canvas_p0, const ImVec2& canvas_p1);
            void render_grid(ImDrawList* drawList, const ImVec2& canvas_p0, const ImVec2& canvas_p1);
            void render_camera_box(ImDrawList* drawList, const ImVec2& canvas_p0, const ImVec2& canvas_p1);

            void render_metrics_window();
        public:
            LevelEditor();
            void render_tab(GLFWwindow *window);
    };
}

#endif
