#ifndef _OMNISCIA_EDITOR_ASSETS_VIEW_WINDOW_H_
#define _OMNISCIA_EDITOR_ASSETS_VIEW_WINDOW_H_

#include <iostream>
#include <string>

#include "../gfx.h"
#include "../types.h"

#include "app_window.h"

#include "../systems/texture_manager.h"

namespace omniscia_editor::windows {
    using namespace omni::types;
    using namespace omniscia_editor::systems;

    class AssetsViewWindow : public AppWindow {
        struct ManagerInstance {
            std::string _label;
            AssetManager* _manager;
        };

        private:
            i32 selectedManagerId;

            std::vector<ManagerInstance> _managers;

        public:
            friend class omni::reflector::FieldFriendlyScope;
            friend class omni::reflector::Reflection<AssetsViewWindow>;

            AssetsViewWindow();

            void render_window() override;

            void render_properties() override;

            static AssetsViewWindow& get_instance();
    };
}

template<>																	               
struct omni::reflector::Reflection<omniscia_editor::windows::AssetsViewWindow> {									               
    const constexpr static std::type_info &typeInfo = typeid(omniscia_editor::windows::AssetsViewWindow);           
    const constexpr static auto clearTypeName = "AssetsViewWindow";
    const constexpr static auto meta = std::make_tuple(
    );																		               
};

#endif
