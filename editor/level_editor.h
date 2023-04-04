#ifndef _OMNISCIA_EDITOR_LEVEL_EDITOR_H_
#define _OMNISCIA_EDITOR_LEVEL_EDITOR_H_

#include <corecrt_math.h>
#include <sstream>
#include <iomanip>

#include "level_editor_properties.h"
#include "level/level_data.h"
#include "file_explorer/files_explorer.h"
#include "gfx.h"

namespace omniscia_editor::level_editor {
    class LevelEditor : public LevelEditorProperties {
        private:
            LevelData _levelData;

            void render_editor_options(GLFWwindow* window);
            void render_level_options();
            void render_tilegroup_options();
            void render_brush_options();

            void render_tiles(ImDrawList* drawList, const ImVec2& canvas_p0, const ImVec2& canvas_p1);
            void render_grid(ImDrawList* drawList, const ImVec2& canvas_p0, const ImVec2& canvas_p1);
            void render_camera_box(ImDrawList* drawList, const ImVec2& canvas_p0, const ImVec2& canvas_p1);

            void render_metrics_window();
        public:
            LevelEditor();
            void render_tab(GLFWwindow *window);
    };
}

#endif
