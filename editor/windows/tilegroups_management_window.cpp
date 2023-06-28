#include "tilegroups_management_window.h"

#include "../systems/level_manager.h"

omniscia_editor::windows::TileGroupsManagementWindow::TileGroupsManagementWindow() {
    _visibleTileGroups = 5.0f;
    selectedTileGroupIndex = 1;
    selectedSortingAlgorithm = 1;
};

void omniscia_editor::windows::TileGroupsManagementWindow::render_window() {
    using namespace omniscia_editor::systems;

    if(!ImGui::Begin("Tile groups")) {
        ImGui::End();
        return;
    }

    LevelData& levelData = LevelManager::get_instance()._levelData;

    if (ImGui::TreeNodeEx("Tile groups list", ImGuiTreeNodeFlags_DefaultOpen)) {
        if (ImGui::BeginListBox("##listbox 2", ImVec2(-FLT_MIN, _visibleTileGroups * ImGui::GetTextLineHeightWithSpacing()))) {
            for (i32 n = 0; n < levelData._tileGroups.size(); n++) {
                const bool is_selected = (selectedTileGroupIndex == n);

                if (ImGui::Selectable(levelData._tileGroups[n]._name.c_str(), is_selected))
                    selectedTileGroupIndex = n;

                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }

            ImGui::EndListBox();
        }

        ImGui::TreePop();
    }
    ImGui::Separator();

    if (ImGui::TreeNodeEx("Actions", ImGuiTreeNodeFlags_DefaultOpen)) {
        if(ImGui::Button("Add tile group")) {
            const std::string tileGroupName = "Unnamed tile group " + std::to_string(levelData._tileGroups.size());

            levelData._tileGroups.push_back(TileGroupData(tileGroupName));
        }
        ImGui::SameLine();
        
        if(ImGui::Button("Delete tile group")) {
            if(selectedTileGroupIndex < levelData._tileGroups.size()) {
                levelData._tileGroups.erase(levelData._tileGroups.begin() + selectedTileGroupIndex);
            }

            --selectedTileGroupIndex;

            if(selectedTileGroupIndex < 1)
                selectedTileGroupIndex = 1; 
        }
        ImGui::SameLine();
        
        if(ImGui::Button("Copy tile group")) {
            if(selectedTileGroupIndex < levelData._tileGroups.size()) {
                TileGroupData tileGroupCopy = levelData._tileGroups[selectedTileGroupIndex];

                tileGroupCopy._name += " copy";

                levelData._tileGroups.push_back(tileGroupCopy);
            }
        }

        ImGui::TreePop();
    }
    ImGui::Separator();

    if (ImGui::TreeNodeEx("Sort", ImGuiTreeNodeFlags_DefaultOpen)) {
        const char* items[] = { "Alphabetical order", "Tile count", "Collision box count" };

        const char* combo_preview_value = items[selectedSortingAlgorithm];

        ImGui::Text("Sorting criteria ");
        ImGui::SameLine();
        if (ImGui::BeginCombo("## sorting criteria", combo_preview_value, ImGuiComboFlags_None)) {
            for (int n = 0; n < IM_ARRAYSIZE(items); n++) {
                const bool is_selected = (selectedSortingAlgorithm == n);

                if (ImGui::Selectable(items[n], is_selected))
                    selectedSortingAlgorithm = n;

                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }

        ImGui::Text("Reverse sort");
        ImGui::SameLine();

        static bool reverseSort = false;
        ImGui::Checkbox("## reverse sort checkbox", &reverseSort);

        ImGui::Button("Sort tile groups");
        
        ImGui::TreePop();
    }

    ImGui::End();
}

void omniscia_editor::windows::TileGroupsManagementWindow::render_properties() {
    PropertiesFieldQuery::property_window_edit_query(*this);
}

omniscia_editor::windows::TileGroupsManagementWindow& omniscia_editor::windows::TileGroupsManagementWindow::get_instance() {
    static TileGroupsManagementWindow window;
    return window;
}
