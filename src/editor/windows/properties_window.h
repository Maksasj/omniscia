#ifndef _OMNISCIA_EDITOR_PROPERTIES_WINDOW_H_
#define _OMNISCIA_EDITOR_PROPERTIES_WINDOW_H_

#include <iostream>
#include <string>

#include "app_window.h"

#include "history_window.h"
#include "level_preview_window.h"
#include "metrics_window.h"
#include "tilegroups_management_window.h"
#include "selected_tilegroup_window.h"
#include "assets_view_window.h"
#include "tools_window.h"

#include "gfx.h"
#include "types.h"

namespace omniscia_editor::windows {
    using namespace omni::types;

    class PropertiesWindow : public AppWindow {
        struct PropertyInstance {
            std::string _label;
            AppWindow* _window;
        };

        private:
            std::vector<PropertyInstance> _windows;

        public:
            friend class omni::reflector::FieldFriendlyScope;
            friend class omni::reflector::Reflection<PropertiesWindow>;

            PropertiesWindow() {
                _windows.push_back(PropertyInstance{"Tools",                &ToolsWindow::get_instance()});
                _windows.push_back(PropertyInstance{"History",              &HistoryWindow::get_instance()});
                _windows.push_back(PropertyInstance{"Level prieview",       &LevelPreviewWindow::get_instance()});
                _windows.push_back(PropertyInstance{"Assets view",          &AssetsViewWindow::get_instance()});
                _windows.push_back(PropertyInstance{"Metrics",              &MetricsWindow::get_instance()});
                _windows.push_back(PropertyInstance{"Tile groups",          &TileGroupsManagementWindow::get_instance()});
                _windows.push_back(PropertyInstance{"Selected tile group",  &SelectedTileGroupWindow::get_instance()});
                
                _windows.push_back(PropertyInstance{"Properties",           this});
            };

            void render_window() override {
                ImGui::SetNextWindowSize(ImVec2(500, 440), ImGuiCond_FirstUseEver);
                if(!ImGui::Begin("Properties", nullptr, ImGuiWindowFlags_None)) {
                    ImGui::End();
                    return;
                }

                ImGui::BeginChild("left pane", ImVec2(150, 0), true);
                    static size_t selected = 0;
                    for(size_t i = 0; i < _windows.size(); ++i)
                        if (ImGui::Selectable(_windows[i]._label.c_str(), selected == i))
                            selected = i;
                ImGui::EndChild();

                ImGui::SameLine();

                ImGui::BeginGroup();
                    ImGui::BeginChild("item view", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()));
                    ImGui::Text("%s", _windows[selected]._label.c_str());
                    ImGui::Separator();
                    if (ImGui::BeginTabBar("##Tabs", ImGuiTabBarFlags_None)) {
                        if (ImGui::BeginTabItem("General")) {

                            _windows[selected]._window->render_properties();

                            ImGui::EndTabItem();
                        }
                        ImGui::EndTabBar();
                    }
                    ImGui::EndChild();
                ImGui::EndGroup();

                ImGui::End();
            }

            void render_properties() override {
                PropertiesFieldQuery::property_window_edit_query(*this);
            }

            static PropertiesWindow& get_instance() {
                static PropertiesWindow window;
                return window;
            }
    };
}



template<>																	               
struct omni::reflector::Reflection<omniscia_editor::windows::PropertiesWindow> {									               
    const constexpr static std::type_info &typeInfo = typeid(omniscia_editor::windows::PropertiesWindow);           
    const constexpr static auto clearTypeName = "PropertiesWindow";
    const constexpr static auto meta = std::make_tuple(
    );																		               
};

#endif
