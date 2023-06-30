#ifndef _OMNISCIA_EDITOR_TOOLS_WINDOW_H_
#define _OMNISCIA_EDITOR_TOOLS_WINDOW_H_

#include <iostream>
#include <string>

#include "../gfx.h"
#include "../types.h"

#include "../tools/base_tool.h"

#include "app_window.h"

namespace omniscia_editor::windows {
    using namespace omni::types;
    using namespace omniscia_editor::tools;

    class ToolsWindow : public AppWindow  {
        private:
            struct ToolInstance {
                std::string _label;
                BaseTool* _tool;
            }; 

            i32 selectedToolIndex;
            std::vector<ToolInstance> _tools;
        public:
            friend class omni::reflector::FieldFriendlyScope;
            friend class omni::reflector::Reflection<ToolsWindow>;

            ToolsWindow() {
                selectedToolIndex = 0;
                
                _tools.push_back({"Pencil",     &PencilTool::get_instance()});
                _tools.push_back({"Selection",  &PencilTool::get_instance()});
                _tools.push_back({"Move",       &PencilTool::get_instance()});
            };

            void render_window() override {
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

            void render_properties() override {
                PropertiesFieldQuery::property_window_edit_query(*this);
            }

            static ToolsWindow& get_instance() {
                static ToolsWindow window;
                return window;
            }
    };
}

template<>																	               
struct omni::reflector::Reflection<omniscia_editor::windows::ToolsWindow> {									               
    const constexpr static std::type_info &typeInfo = typeid(omniscia_editor::windows::ToolsWindow);           
    const constexpr static auto clearTypeName = "ToolsWindow";
    const constexpr static auto meta = std::make_tuple(
    );																		               
};

#endif
