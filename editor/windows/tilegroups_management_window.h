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
            i32 selectedTileGroupIndex;
            i32 selectedSortingAlgorithm;

            f32 _visibleTileGroups;

        public:
            friend class omni::reflector::FieldFriendlyScope;
            friend class omni::reflector::Reflection<TileGroupsManagementWindow>;

            TileGroupsManagementWindow();

            void render_window() override;

            void render_properties() override;

            static TileGroupsManagementWindow& get_instance();
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
