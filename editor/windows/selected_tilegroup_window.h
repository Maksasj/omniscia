#ifndef _OMNISCIA_EDITOR_SELECTED_TILEGROUP_WINDOW_H_
#define _OMNISCIA_EDITOR_SELECTED_TILEGROUP_WINDOW_H_

#include <iostream>
#include <string>

#include "../gfx.h"
#include "../types.h"

#include "app_window.h"

namespace omniscia_editor::windows {
    using namespace omni::types;

    class SelectedTileGroup : public AppWindow  {
        private:

        public:
            friend class omni::reflector::FieldFriendlyScope;
            friend class omni::reflector::Reflection<SelectedTileGroup>;

            SelectedTileGroup() {

            };

            void render_window() override {
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

            void render_properties() override {
                PropertiesFieldQuery::property_window_edit_query(*this);
            }

            static SelectedTileGroup& get_instance() {
                static SelectedTileGroup window;
                return window;
            }
    };
}

template<>																	               
struct omni::reflector::Reflection<omniscia_editor::windows::SelectedTileGroup> {									               
    const constexpr static std::type_info &typeInfo = typeid(omniscia_editor::windows::SelectedTileGroup);           
    const constexpr static auto clearTypeName = "SelectedTileGroup";
    const constexpr static auto meta = std::make_tuple(
        // omni::reflector::FieldFriendlyScope::field_registration(&omniscia_editor::windows::HistoryWindow::_visibleSteps, "Visible steps"),
        // omni::reflector::FieldFriendlyScope::field_registration(&omniscia_editor::windows::HistoryWindow::_autoScroll, "Auto scroll")
    );																		               
};

#endif
