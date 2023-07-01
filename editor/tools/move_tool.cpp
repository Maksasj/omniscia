#include "move_tool.h"

omniscia_editor::tools::MoveTool::MoveTool() {

}

void omniscia_editor::tools::MoveTool::render_effect() {
    ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeAll);
}

omniscia_editor::tools::MoveTool& omniscia_editor::tools::MoveTool::get_instance() {
    static MoveTool tool;
    return tool;
}
