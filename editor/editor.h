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
#include "windows/metrics_window.h"
#include "windows/selected_tilegroup_window.h"
#include "windows/tilegroups_management_window.h"
#include "windows/assets_view_window.h"

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

                static bool renderBrushWindow = true;
                static bool renderLevelPreviewWindow = true;
                static bool renderHistroyWindow = true;
                static bool renderMetricsWindow = true;
                static bool renderTileGroupsManagementWindow = true;
                static bool renderSelectedTileGroupWindow = true;
                static bool renderAssetsViewWindow = true;

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
                        ImGui::MenuItem("Assets view", nullptr, &renderAssetsViewWindow);

                        ImGui::Separator();

                        if (ImGui::BeginMenu("Tile groups")) {
                            ImGui::MenuItem("Tile groups", nullptr, &renderTileGroupsManagementWindow);
                            ImGui::MenuItem("Selected tile group", nullptr, &renderSelectedTileGroupWindow);

                            ImGui::EndMenu();
                        }

                        if (ImGui::BeginMenu("Tile")) {
                            ImGui::MenuItem("Tile preview", nullptr, nullptr);
                            ImGui::MenuItem("Tile editor", nullptr, nullptr);

                            ImGui::EndMenu();
                        }
                        ImGui::Separator();

                        ImGui::MenuItem("Metrics", nullptr, &renderMetricsWindow);

                        ImGui::EndMenu();
                    }
                    if (ImGui::MenuItem("Properties", nullptr, nullptr)) {
                        renderPropertiesWindow = !renderPropertiesWindow;
                    }

                    ImGui::EndMenuBar();
                }
                
                ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
                ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);

                if(renderBrushWindow) BrushWindow::get_instance().render_window();
                if(renderLevelPreviewWindow) LevelPreviewWindow::get_instance().render_window();
                if(renderHistroyWindow) HistoryWindow::get_instance().render_window();
                if(renderMetricsWindow) MetricsWindow::get_instance().render_window();
                if(renderTileGroupsManagementWindow) TileGroupsManagementWindow::get_instance().render_window();
                if(renderSelectedTileGroupWindow) SelectedTileGroup::get_instance().render_window();
                if(renderAssetsViewWindow) AssetsViewWindow::get_instance().render_window();

                if(renderPropertiesWindow) PropertiesWindow::get_instance().render_window();

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
