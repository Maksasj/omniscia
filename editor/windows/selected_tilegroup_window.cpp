#include "selected_tilegroup_window.h"

omniscia_editor::windows::SelectedTileGroupWindow::SelectedTileGroupWindow() {

};

void omniscia_editor::windows::SelectedTileGroupWindow::render_window() {
    if(!ImGui::Begin("Selected tile group")) {
        ImGui::End();
        return;
    }

    ImGui::Text("Unnamed tile group");
    ImGui::Separator();

    if (ImGui::TreeNodeEx("General", ImGuiTreeNodeFlags_DefaultOpen)) {
        ImGui::Text("Name");
        ImGui::SameLine();
        static char buf1[256] = ""; 
        ImGui::InputText("## Export path", buf1, 256);
        ImGui::SameLine();
        ImGui::Button("Clear");
        
        static ImVec4 color = ImVec4(255.0f, 255.0f, 255.0f, 255.0f);

        ImGui::Text("Associative color");
        ImGui::SameLine();

        bool open_popup = ImGui::ColorButton("Associative color ##3b", color, ImGuiColorEditFlags_None);
        ImGui::SameLine(0, ImGui::GetStyle().ItemInnerSpacing.x);
        open_popup |= ImGui::Button("Palette");
        if (open_popup)
            ImGui::OpenPopup("associativeColorPicker");

        if (ImGui::BeginPopup("associativeColorPicker")) {
            ImGui::Text("Associative color picker");
            ImGui::Separator();
            ImGui::ColorPicker4("##picker", (float*)&color, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoSmallPreview);
            ImGui::SameLine();

            ImGui::BeginGroup();
            ImGui::Text("Current");
            ImGui::ColorButton("##current", color, ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_AlphaPreviewHalf, ImVec2(60, 40));
            
            ImGui::EndGroup();
            ImGui::EndPopup();
        }

        ImGui::TreePop();
    }

    if (ImGui::TreeNodeEx("Tiles", ImGuiTreeNodeFlags_DefaultOpen)) {
        
        ImGui::TreePop();
    }

    ImGui::End();
}

void omniscia_editor::windows::SelectedTileGroupWindow::render_properties() {
    PropertiesFieldQuery::property_window_edit_query(*this);
}

omniscia_editor::windows::SelectedTileGroupWindow& omniscia_editor::windows::SelectedTileGroupWindow::get_instance() {
    static SelectedTileGroupWindow window;
    return window;
}
