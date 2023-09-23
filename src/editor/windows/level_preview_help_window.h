#ifndef _OMNISCIA_EDITOR_LEVEL_PREVIEW_HELP_WINDOW_H_
#define _OMNISCIA_EDITOR_LEVEL_PREVIEW_HELP_WINDOW_H_

#include <iostream>
#include <string>

#include "gfx.h"
#include "types.h"

#include "app_window.h"
#include "level_preview_window.h"

namespace omniscia_editor::windows {
    using namespace omni::types;

    class LevelPreviewHelpWindow : public AppWindow {
        private:

        public:
            friend class omni::reflector::FieldFriendlyScope;
            friend class omni::reflector::Reflection<LevelPreviewHelpWindow>;

            LevelPreviewHelpWindow() {

            };

            void render_window() override {
                if(!ImGui::Begin("Level preview help")) {
                    ImGui::End();
                    return;
                }

                ImGui::Text("Zoom ");
                    ImGui::SameLine();
                    ImGui::SliderFloat("## zoom slider", &LevelPreviewWindow::get_instance()._zoom, LevelPreviewWindow::get_instance()._minZoom, LevelPreviewWindow::get_instance()._maxZoom, "%.3f");

                ImGui::Separator();

                ImGui::Text("Scroll ");
                    ImGui::Text("X ");
                    ImGui::SameLine();
                    ImGui::DragFloat("## scroll slider x", &LevelPreviewWindow::get_instance()._scroll.x, 0.5f);
                    ImGui::Text("Y ");
                    ImGui::SameLine();
                    ImGui::DragFloat("## scroll slider y", &LevelPreviewWindow::get_instance()._scroll.y, 0.5f);

                ImGui::Separator();

                ImGui::Text("Cursor position");
                    ImGui::Text("(x: %.3f, y: %.3f]", LevelPreviewWindow::get_instance()._cursorPos.x, LevelPreviewWindow::get_instance()._cursorPos.y);

                ImGui::End();
            }

            void render_properties() override {
                PropertiesFieldQuery::property_window_edit_query(*this);
            }

            static LevelPreviewHelpWindow& get_instance() {
                static LevelPreviewHelpWindow window;
                return window;
            }
    };
}

template<>																	               
struct omni::reflector::Reflection<omniscia_editor::windows::LevelPreviewHelpWindow> {									               
    const constexpr static std::type_info &typeInfo = typeid(omniscia_editor::windows::LevelPreviewHelpWindow);           
    const constexpr static auto clearTypeName = "LevelPreviewHelpWindow";
    const constexpr static auto meta = std::make_tuple(
    );																		               
};

#endif
