#ifndef _OMNISCIA_EDITOR_START_TAB_H_
#define _OMNISCIA_EDITOR_START_TAB_H_

#include <string>

#include "gfx.h"

namespace omniscia_editor::editor {
    class StartTab {
        private:
            void text_centered(const char* text) const {
                float win_width = ImGui::GetWindowSize().x;
                float text_width = ImGui::CalcTextSize(text).x;
                float text_indentation = (win_width - text_width) * 0.5f;
                float min_indentation = 20.0f;

                if (text_indentation <= min_indentation)
                    text_indentation = min_indentation;

                ImGui::SameLine(text_indentation);
                ImGui::PushTextWrapPos(win_width - text_indentation);
                ImGui::TextWrapped("%s", text);
                ImGui::PopTextWrapPos();
            }
            
        public:
            void render_tab() const {
                if(ImGui::BeginTabItem("Main")) {
                    //text_centered("Hello world!");

                    ImGui::TextColored(ImVec4(1.0, 1.0, 0.1, 1.0), "Hello world!");
                    ImGui::EndTabItem();
                }
            };
    };
}

#endif
