#include "selected_tilegroup_window.h"

#include "tilegroups_management_window.h"

#include "../systems/level_manager.h"

omniscia_editor::windows::SelectedTileGroupWindow::SelectedTileGroupWindow() {

};

void TextCentered(const std::string& text) {
    const auto windowWidth = ImGui::GetWindowSize().x;
    const auto textWidth   = ImGui::CalcTextSize(text.c_str()).x;
    const auto windowHeight = ImGui::GetWindowSize().y;
    const auto textHeight   = ImGui::CalcTextSize(text.c_str()).y;

    ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
    ImGui::SetCursorPosY((windowHeight - textHeight) * 0.5f);
    ImGui::Text("%s", text.c_str());
}

void omniscia_editor::windows::SelectedTileGroupWindow::render_window() {
    using namespace omniscia_editor::systems;

    if(!ImGui::Begin("Selected tile group")) {
        ImGui::End();
        return;
    }

    const i32 selectedTileGroupIndex = TileGroupsManagementWindow::get_instance().get_selected_tile_group_index();
    LevelData& levelData = LevelManager::get_instance()._levelData;

    if(selectedTileGroupIndex > static_cast<i32>(levelData._tileGroups.size()) - 1) {
        TextCentered("No tile group selected");
        ImGui::End();
        return;
    }

    TileGroupData& selectedTileGroup = levelData._tileGroups[selectedTileGroupIndex];

    ImGui::Text("%s", selectedTileGroup._name.c_str());
    ImGui::Separator();

    if (ImGui::TreeNodeEx("General", ImGuiTreeNodeFlags_DefaultOpen)) {
        std::string& name = selectedTileGroup._name;

        ImGui::Text("Name");
        char buffer[256] = { 0 };
        name.copy(buffer, name.size());
        ImGui::InputText("## value", buffer, 256);
        ImGui::SameLine();
        name = std::string(buffer);

        if(ImGui::Button("Clear"))
            name.clear();

        ImVec4 temporaryColor = ImVec4(
            selectedTileGroup._tileGroupAssociatedColor.x, 
            selectedTileGroup._tileGroupAssociatedColor.y, 
            selectedTileGroup._tileGroupAssociatedColor.z, 
            selectedTileGroup._tileGroupAssociatedColor.w);

        ImGui::Text("Associative color");
        ImGui::SameLine();

        bool open_popup = ImGui::ColorButton("Associative color ##3b", temporaryColor, ImGuiColorEditFlags_None);
        ImGui::SameLine(0, ImGui::GetStyle().ItemInnerSpacing.x);
        open_popup |= ImGui::Button("Palette");
        if (open_popup)
            ImGui::OpenPopup("associativeColorPicker");

        if (ImGui::BeginPopup("associativeColorPicker")) {
            ImGui::Text("Associative color picker");
            ImGui::Separator();
            ImGui::ColorPicker4("##picker", (float*)&temporaryColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoSmallPreview);
            ImGui::SameLine();

            ImGui::BeginGroup();
            ImGui::Text("Current");
            ImGui::ColorButton("##current", temporaryColor, ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_AlphaPreviewHalf, ImVec2(60, 40));
            
            ImGui::EndGroup();
            ImGui::EndPopup();
        }

        selectedTileGroup._tileGroupAssociatedColor = Vec4f(temporaryColor.x, temporaryColor.y, temporaryColor.z, temporaryColor.w);

        ImGui::TreePop();
    }

    if (ImGui::TreeNodeEx("Tiles", ImGuiTreeNodeFlags_DefaultOpen)) {
        std::string& textureAssetID = selectedTileGroup._textureMaterialAssetId;

        ImGui::Text("Texture material asset id");
        char buffer[256] = { 0 };
        textureAssetID.copy(buffer, textureAssetID.size());
        ImGui::InputText("## value", buffer, 256);
        ImGui::SameLine();
        textureAssetID = std::string(buffer);

        if(ImGui::Button("Clear"))
            textureAssetID.clear();


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
