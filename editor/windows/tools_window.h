#ifndef _OMNISCIA_EDITOR_TOOLS_WINDOW_H_
#define _OMNISCIA_EDITOR_TOOLS_WINDOW_H_

#include <iostream>
#include <string>

#include "../gfx.h"
#include "../types.h"

#include "app_window.h"

namespace omniscia_editor::windows {
    using namespace omni::types;

    class ToolsWindow : public AppWindow  {
        private:

        public:
            friend class omni::reflector::FieldFriendlyScope;
            friend class omni::reflector::Reflection<ToolsWindow>;

            ToolsWindow() {

            };

            void render_window() override {
                if(!ImGui::Begin("Tools")) {
                    ImGui::End();
                    return;
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
