#include "assets_view_window.h"

omniscia_editor::windows::AssetsViewWindow::AssetsViewWindow() {
    _managers.push_back({"Textures", &TextureManager::get_instance()});
};

void omniscia_editor::windows::AssetsViewWindow::render_window() {
    if(!ImGui::Begin("Assets view")) {
        ImGui::End();
        return;
    }

    const auto windowSize = ImGui::GetWindowSize();

    ImGui::BeginChild("ChildL", ImVec2(windowSize.x / 4.0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);
        if (ImGui::BeginListBox("##listbox 3", ImVec2(-FLT_MIN, -FLT_MIN))) {
            for (int n = 0; n < _managers.size(); n++) {
                const bool isSelected = (selectedManagerId == n);
                if (ImGui::Selectable(_managers[n]._label.c_str(), isSelected))
                    selectedManagerId = n;

                if (isSelected)
                    ImGui::SetItemDefaultFocus();
            }

            ImGui::EndListBox();
        }
    ImGui::EndChild();

    ImGui::SameLine();

    // ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
    ImGui::BeginChild("ChildR", ImVec2(-FLT_MIN, -FLT_MIN), true, ImGuiWindowFlags_None);

    ImGui::Text("%s", _managers[selectedManagerId]._label.c_str());

    AssetManager* activeManager = _managers[selectedManagerId]._manager; 

    if(ImGui::Button("Reaload assets")) {
        activeManager->reload_assets("assets/texture_assets.json");
    }
    ImGui::SameLine();

    static bool assetPreview = true;

    ImGui::Checkbox("Asset preview", &assetPreview);
    activeManager->render_asset_preview(assetPreview);

    ImGui::EndChild();
    // ImGui::PopStyleVar();

    ImGui::End();
}

void omniscia_editor::windows::AssetsViewWindow::render_properties() {
    PropertiesFieldQuery::property_window_edit_query(*this);
}

omniscia_editor::windows::AssetsViewWindow& omniscia_editor::windows::AssetsViewWindow::get_instance() {
    static AssetsViewWindow window;
    return window;
}
