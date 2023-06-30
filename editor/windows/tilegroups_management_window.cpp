#include "tilegroups_management_window.h"

#include "../systems/level_manager.h"

omniscia_editor::windows::TileGroupsManagementWindow::TileGroupsManagementWindow() {
    _visibleTileGroups = 5.0f;
    _selectedTileGroupIndex = 0;
    _selectedSortingAlgorithm = 0;

    _reverseSort = false;
    _tileGroupSorters.push_back({"Alphabetical order",  &AlphabeticalTileGroupSorter::get_instance()});
    _tileGroupSorters.push_back({"Tile count",          &TileCountTileGroupSorter::get_instance()});
    _tileGroupSorters.push_back({"Collision box count", &CollisionBoxCountTileGroupSorter::get_instance()});
};

omni::types::i32 omniscia_editor::windows::TileGroupsManagementWindow::get_selected_tile_group_index() const {
    return _selectedTileGroupIndex;
}

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
                const bool is_selected = (_selectedTileGroupIndex == n);

                std::stringstream ss;
                ss << levelData._tileGroups[n]._name << "## " << (void*) &levelData._tileGroups[n];
                
                if (ImGui::Selectable(ss.str().c_str(), is_selected))
                    _selectedTileGroupIndex = n;

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
            if(_selectedTileGroupIndex < levelData._tileGroups.size()) {
                levelData._tileGroups.erase(levelData._tileGroups.begin() + _selectedTileGroupIndex);
            }

            --_selectedTileGroupIndex;

            if(_selectedTileGroupIndex < 0)
                _selectedTileGroupIndex = 0; 
        }
        ImGui::SameLine();
        
        if(ImGui::Button("Copy tile group")) {
            if(_selectedTileGroupIndex < levelData._tileGroups.size()) {
                TileGroupData tileGroupCopy = levelData._tileGroups[_selectedTileGroupIndex];

                tileGroupCopy._name += " copy";

                levelData._tileGroups.push_back(tileGroupCopy);
            }
        }

        ImGui::TreePop();
    }
    ImGui::Separator();

    if (ImGui::TreeNodeEx("Sort", ImGuiTreeNodeFlags_DefaultOpen)) {
        ImGui::Text("Sorting criteria ");
        ImGui::SameLine();
        if (ImGui::BeginCombo("## sorting criteria", _tileGroupSorters[_selectedSortingAlgorithm]._label.c_str(), ImGuiComboFlags_None)) {
            for (i32 n = 0; n < _tileGroupSorters.size(); n++) {
                const bool is_selected = (_selectedSortingAlgorithm == n);

                if (ImGui::Selectable(_tileGroupSorters[n]._label.c_str(), is_selected))
                    _selectedSortingAlgorithm = n;

                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }

        ImGui::Text("Reverse sort");
        ImGui::SameLine();

        ImGui::Checkbox("## reverse sort checkbox", &_reverseSort);

        if(ImGui::Button("Sort tile groups"))
            _tileGroupSorters[_selectedSortingAlgorithm]._sorter->sort(levelData._tileGroups, _reverseSort);
        
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
