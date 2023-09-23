#ifndef _OMNISCIA_EDITOR_TOOLS_WINDOW_H_
#define _OMNISCIA_EDITOR_TOOLS_WINDOW_H_

#include <iostream>
#include <string>

#include "gfx.h"
#include "types.h"

#include "tools/base_tool.h"

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
            friend class LevelPreviewWindow;

            ToolsWindow();

            void render_window() override;

            void render_properties() override;

            static ToolsWindow& get_instance();
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
