#ifndef _OMNISCIA_EDITOR_TILE_GROUPS_MANAGEMENT_WINDOW_H_
#define _OMNISCIA_EDITOR_TILE_GROUPS_MANAGEMENT_WINDOW_H_

#include <iostream>
#include <string>

#include "../gfx.h"
#include "../types.h"

#include "app_window.h"

namespace omniscia_editor::windows {
    using namespace omni::types;

    class TileGroupsManagementWindow : public AppWindow  {
        private:
            f32 _visibleTileGroups;

        public:
            friend class omni::reflector::FieldFriendlyScope;
            friend class omni::reflector::Reflection<TileGroupsManagementWindow>;

            TileGroupsManagementWindow() {
                _visibleTileGroups = 5.0f;
            };

            void render_window() override {
                if(!ImGui::Begin("Tile groups")) {
                    ImGui::End();
                    return;
                }

                if (ImGui::TreeNodeEx("Tile groups list", ImGuiTreeNodeFlags_DefaultOpen)) {
                    const char* items[] = { "Apple", "Banana", "Cherry", "Kiwi", "Mango", "Orange", "Pineapple", "Strawberry", "Watermelon" };
                    static int item_current_idx = 1;
                    if (ImGui::BeginListBox("##listbox 2", ImVec2(-FLT_MIN, _visibleTileGroups * ImGui::GetTextLineHeightWithSpacing()))) {
                        for (int n = 0; n < IM_ARRAYSIZE(items); n++) {
                            const bool is_selected = (item_current_idx == n);
                            if (ImGui::Selectable(items[n], is_selected))
                                item_current_idx = n;

                            if (is_selected)
                                ImGui::SetItemDefaultFocus();
                        }

                        ImGui::EndListBox();
                    }

                    ImGui::TreePop();
                }
                ImGui::Separator();

                if (ImGui::TreeNodeEx("Actions", ImGuiTreeNodeFlags_DefaultOpen)) {
                    ImGui::Button("Add tile group");
                    ImGui::SameLine();
                    ImGui::Button("Delete tile group");
                    ImGui::SameLine();
                    ImGui::Button("Copy tile group");

                    ImGui::TreePop();
                }
                ImGui::Separator();

                if (ImGui::TreeNodeEx("Sort", ImGuiTreeNodeFlags_DefaultOpen)) {
                    const char* items[] = { "AAAA", "BBBB", "CCCC", "DDDD", "EEEE", "FFFF", "GGGG", "HHHH", "IIII", "JJJJ", "KKKK", "LLLLLLL", "MMMM", "OOOOOOO" };
                    static int item_current_idx = 0;
                    const char* combo_preview_value = items[item_current_idx];

                    ImGui::Text("Sorting criteria ");
                    ImGui::SameLine();
                    if (ImGui::BeginCombo("## sorting criteria", combo_preview_value, ImGuiComboFlags_None)) {
                        for (int n = 0; n < IM_ARRAYSIZE(items); n++) {
                            const bool is_selected = (item_current_idx == n);
                            if (ImGui::Selectable(items[n], is_selected))
                                item_current_idx = n;

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

            void render_properties() override {
                PropertiesFieldQuery::property_window_edit_query(*this);
            }

            static TileGroupsManagementWindow& get_instance() {
                static TileGroupsManagementWindow window;
                return window;
            }
    };
}

template<>																	               
struct omni::reflector::Reflection<omniscia_editor::windows::TileGroupsManagementWindow> {									               
    const constexpr static std::type_info &typeInfo = typeid(omniscia_editor::windows::TileGroupsManagementWindow);           
    const constexpr static auto clearTypeName = "TileGroupsManagementWindow";
    const constexpr static auto meta = std::make_tuple(
        omni::reflector::FieldFriendlyScope::field_registration(&omniscia_editor::windows::TileGroupsManagementWindow::_visibleTileGroups, "Visible tile groups")
    );																		               
};

#endif
