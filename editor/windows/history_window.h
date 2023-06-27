#ifndef _OMNISCIA_EDITOR_HISTORY_WINDOW_H_
#define _OMNISCIA_EDITOR_HISTORY_WINDOW_H_

#include <iostream>
#include <string>

#include "../gfx.h"
#include "../types.h"

#include "app_window.h"

namespace omniscia_editor::windows {
    using namespace omni::types;

    class HistoryWindow : public AppWindow  {
        private:
        public:
            HistoryWindow() {

            };

            void render_window() override {
                ImGui::Begin("History");

                ImGui::End();
            }

            void render_properties() override {
                PropertiesFieldQuery::property_window_edit_query(*this);
            }

            static HistoryWindow& get_instance() {
                static HistoryWindow window;
                return window;
            }
    };
}

template<>																	               
struct omni::reflector::Reflection<omniscia_editor::windows::HistoryWindow> {									               
    const constexpr static std::type_info &typeInfo = typeid(omniscia_editor::windows::HistoryWindow);           
    const constexpr static auto clearTypeName = "HistoryWindow";
    const constexpr static auto meta = std::make_tuple(
    );																		               
};

#endif
