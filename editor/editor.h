#ifndef _OMNISCIA_EDITOR_EDITOR_H_
#define _OMNISCIA_EDITOR_EDITOR_H_

#include "themes/themes.h"

#include "start_tab.h"
#include "level_editor.h"

namespace omniscia_editor::editor {
    using namespace omni::types;
    using namespace omniscia_editor::level_editor;
    using namespace omniscia_editor::level_editor::themes;

    class Editor {
        private:
            std::vector<Theme*> themes;

            StartTab _startTab;
            LevelEditor _levelEditor;
        public:
            Editor() {
                themes = {
                    new DeepDarkTheme(),
                    new DraculaTheme(),
                    new GreenTheme(),
                    new RedTheme(),
                    new SimpleTheme()
                };
            }

            void render(GLFWwindow *window) {
                ImGui_ImplOpenGL3_NewFrame();
                ImGui_ImplGlfw_NewFrame();
                ImGui::NewFrame();

                auto flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize |ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoMove;

                int sizeX; int sizeY;
                glfwGetWindowSize(window, &sizeX, &sizeY);
                ImGui::SetNextWindowSize({(float)sizeX, (float)sizeY});
                ImGui::SetNextWindowPos({0, 0});
                ImGui::Begin("Omniscia Editor", NULL, flags);

                    ImGui::BeginTabBar("Omniscia Editor Tabs");
                        using namespace omniscia_editor::editor;

                        _startTab.render_tab();
                        _levelEditor.render_tab(window);
                    
                    ImGui::EndTabBar();

                ImGui::End();

                ImGui::Render();
                ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());               
            };
        
        static Editor& get_instance() {
            static Editor editor;
            return editor;
        }
    };
}

#endif
