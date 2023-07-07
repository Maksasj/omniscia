#ifndef _OMNISCIA_EDITOR_SELECTED_TILEGROUP_WINDOW_H_
#define _OMNISCIA_EDITOR_SELECTED_TILEGROUP_WINDOW_H_

#include <iostream>
#include <string>

#include "../gfx.h"
#include "../types.h"

#include "app_window.h"

namespace omniscia_editor::windows {
    using namespace omni::types;

    class SelectedTileGroupWindow : public AppWindow  {
        private:

        public:
            friend class omni::reflector::FieldFriendlyScope;
            friend class omni::reflector::Reflection<SelectedTileGroupWindow>;

            SelectedTileGroupWindow();

            void render_window() override;

            void render_properties() override;
            
            static SelectedTileGroupWindow& get_instance();
    };
}

template<>																	               
struct omni::reflector::Reflection<omniscia_editor::windows::SelectedTileGroupWindow> {									               
    const constexpr static std::type_info &typeInfo = typeid(omniscia_editor::windows::SelectedTileGroupWindow);           
    const constexpr static auto clearTypeName = "SelectedTileGroupWindow";
    const constexpr static auto meta = std::make_tuple(
        // omni::reflector::FieldFriendlyScope::field_registration(&omniscia_editor::windows::HistoryWindow::_visibleSteps, "Visible steps"),
        // omni::reflector::FieldFriendlyScope::field_registration(&omniscia_editor::windows::HistoryWindow::_autoScroll, "Auto scroll")
    );																		               
};

#endif
