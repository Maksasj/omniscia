#ifndef _OMNISCIA_EDITOR_HISTORY_WINDOW_H_
#define _OMNISCIA_EDITOR_HISTORY_WINDOW_H_

#include <iostream>
#include <string>

#include "gfx.h"
#include "types.h"

#include "app_window.h"

namespace omniscia_editor::windows {
    using namespace omni::types;

    class HistoryWindow : public AppWindow  {
        private:
            f32 _visibleSteps;
            bool _autoScroll;

        public:
            friend class omni::reflector::FieldFriendlyScope;
            friend class omni::reflector::Reflection<HistoryWindow>;

            HistoryWindow() {
                _visibleSteps = 8.0;
                _autoScroll = true;
            };

            void render_window() override {
                if(!ImGui::Begin("History")) {
                    ImGui::End();
                    return;
                }

                if (ImGui::BeginChild("scrolling", ImVec2(-FLT_MIN, _visibleSteps * ImGui::GetTextLineHeightWithSpacing()), true, ImGuiWindowFlags_HorizontalScrollbar)) {
                    
                    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
                        
                    ImGuiListClipper clipper;
                    clipper.Begin(500);
                    while (clipper.Step())
                        for (int line_no = clipper.DisplayStart; line_no < clipper.DisplayEnd; line_no++)
                            ImGui::Text("[20:43:00] Added tile");
                    clipper.End();

                    ImGui::PopStyleVar();

                    if (_autoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
                        ImGui::SetScrollHereY(1.0f);

                    ImGui::EndChild();
                }

                ImGui::Text("Auto scroll");
                ImGui::SameLine();
                ImGui::Checkbox("## history auto scroll checkbox", &_autoScroll);
                
                ImGui::SameLine(ImGui::GetWindowSize().x - 2.0f * (ImGui::CalcTextSize("Undo 5 ").x + ImGui::GetStyle().FramePadding.x * 2.0f));

                ImGui::Button("Undo");
                ImGui::SameLine();
                ImGui::Button("Undo 5");

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
        omni::reflector::FieldFriendlyScope::field_registration(&omniscia_editor::windows::HistoryWindow::_visibleSteps, "Visible steps"),
        omni::reflector::FieldFriendlyScope::field_registration(&omniscia_editor::windows::HistoryWindow::_autoScroll, "Auto scroll")
    );
};

#endif
