#ifndef _OMNISCIA_EDITOR_EDITOR_H_
#define _OMNISCIA_EDITOR_EDITOR_H_

#include "themes/themes.h"

#include "start_tab.h"
#include "level_editor.h"
#include "level_editor_new.h"

#include "windows/level_preview_window.h"
#include "windows/properties_window.h"
#include "windows/history_window.h"
#include "windows/brush_window.h"

namespace omniscia_editor::editor {
    using namespace omni::types;
    using namespace omniscia_editor::level_editor;
    using namespace omniscia_editor::level_editor::themes;

    using namespace omniscia_editor::windows;

    class Editor {
        private:
            std::vector<Theme*> themes;

            StartTab _startTab;
            LevelEditorOld _levelEditor;
        public:
            Editor() {
                themes = {
                    new DeepDarkTheme(),
                    new DraculaTheme(),
                    new GreenTheme(),
                    new RedTheme(),
                    new SimpleTheme()
                };

                themes[0]->apply_theme();
            }

            void render(GLFWwindow *window) {
                static bool open = true;

                ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

                const ImGuiViewport* viewport = ImGui::GetMainViewport();
                ImGui::SetNextWindowPos(viewport->WorkPos);
                ImGui::SetNextWindowSize(viewport->WorkSize);
                ImGui::SetNextWindowViewport(viewport->ID);
                ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
                ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
                ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
                window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
                window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
                
                ImGui::Begin("DockSpace Demo", &open, window_flags);

                ImGui::PopStyleVar();
                ImGui::PopStyleVar();
                ImGui::PopStyleVar();

                static bool renderBrushWindow = false;
                static bool renderLevelPreviewWindow = false;
                static bool renderHistroyWindow = false;

                static bool renderPropertiesWindow = false;

                if (ImGui::BeginMenuBar()) {
                    if (ImGui::BeginMenu("File")) {
                        if(ImGui::MenuItem("New", nullptr, nullptr)) {
                            
                        };
                        ImGui::Separator();

                        if(ImGui::MenuItem("Open", nullptr, nullptr)) {
                                
                        };

                        if(ImGui::MenuItem("Open Recent", nullptr, nullptr)) {
                                
                        };
                        ImGui::Separator();

                        if(ImGui::MenuItem("Save", nullptr, nullptr)) {
                                
                        };
                        ImGui::Separator();

                        if(ImGui::MenuItem("Exit", nullptr, nullptr)) {
                                
                        };

                        ImGui::EndMenu();
                    }
                    if (ImGui::BeginMenu("View")) {
                        ImGui::MenuItem("Brush", nullptr, &renderBrushWindow);
                        ImGui::MenuItem("Level preview", nullptr, &renderLevelPreviewWindow);
                        ImGui::MenuItem("History", nullptr, &renderHistroyWindow);

                        ImGui::EndMenu();
                    }
                    if (ImGui::MenuItem("Properties", nullptr, nullptr)) {
                        renderPropertiesWindow = !renderPropertiesWindow;
                    }

                    ImGui::EndMenuBar();
                }
                
                ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
                ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);

                // ImGui::Begin("Brush");
                    // const char* items[] = { "AAAA", "BBBB", "CCCC", "DDDD", "EEEE", "FFFF", "GGGG", "HHHH", "IIIIIII", "JJJJ", "KKKKKKK" };
                    // static int item_current = 0;
                    // ImGui::Combo("combo", &item_current, items, IM_ARRAYSIZE(items));
                // ImGui::End();

                // ImGui::Begin("History");
                // ImGui::End();


                if(renderBrushWindow) BrushWindow::get_instance().render_window();
                if(renderLevelPreviewWindow) LevelPreviewWindow::get_instance().render_window();
                if(renderHistroyWindow) HistoryWindow::get_instance().render_window();

                if(renderPropertiesWindow) PropertiesWindow::get_instance().render_window();

                // LevelEditor::get_instance().render();
                // ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
                // ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), 0);
                /*
                auto flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize |ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoMove;

                int sizeX; int sizeY;
                glfwGetWindowSize(window, &sizeX, &sizeY);
                ImGui::SetNextWindowSize({(float)sizeX, (float)sizeY});
                ImGui::SetNextWindowPos({0, 0});
                ImGui::Begin("Omniscia Editor", nullptr, flags);
                    ImGui::BeginTabBar("Omniscia Editor Tabs");
                        using namespace omniscia_editor::editor;

                        // _startTab.render_tab();

                    //     _levelEditor.render_tab(window);
                    // 
                    ImGui::EndTabBar();
                ImGui::End();
                */

                ImGui::ShowDemoWindow();

                ImGui::End();          
            };
        
        static Editor& get_instance() {
            static Editor editor;
            return editor;
        }
    };
}

#endif
