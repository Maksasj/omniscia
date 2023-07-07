#include "tools_window.h"

#include "tools/pencil_tool.h"
#include "tools/selection_tool.h"
#include "tools/move_tool.h"

omniscia_editor::windows::ToolsWindow::ToolsWindow() {
    selectedToolIndex = 0;
    
    _tools.push_back({"Pencil",     &PencilTool::get_instance()});
    _tools.push_back({"Selection tool",  &SelectionTool::get_instance()});
    _tools.push_back({"Move tool",       &MoveTool::get_instance()});
};

void omniscia_editor::windows::ToolsWindow::render_window() {
    if(!ImGui::Begin("Tools")) {
        ImGui::End();
        return;
    }

    if (ImGui::BeginCombo("Tools", _tools[selectedToolIndex]._label.c_str(), ImGuiComboFlags_None)) {
        for (int n = 0; n < _tools.size(); n++) {
            const bool is_selected = (selectedToolIndex == n);
            if (ImGui::Selectable(_tools[n]._label.c_str(), is_selected))
                selectedToolIndex = n;

            if (is_selected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }

    ImGui::End();
}

void omniscia_editor::windows::ToolsWindow::render_properties() {
    PropertiesFieldQuery::property_window_edit_query(*this);
}

omniscia_editor::windows::ToolsWindow& omniscia_editor::windows::ToolsWindow::get_instance() {
    static ToolsWindow window;
    return window;
}
