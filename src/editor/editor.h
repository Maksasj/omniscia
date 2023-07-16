#ifndef _OMNISCIA_EDITOR_EDITOR_H_
#define _OMNISCIA_EDITOR_EDITOR_H_

#include "windows/level_preview_help_window.h"
#include "windows/level_preview_window.h"
#include "windows/properties_window.h"
#include "windows/history_window.h"
#include "windows/metrics_window.h"
#include "windows/selected_tilegroup_window.h"
#include "windows/tilegroups_management_window.h"
#include "windows/assets_view_window.h"
#include "windows/tools_window.h"
#include "windows/themes_window.h"

#include "systems/level_manager.h"

namespace omniscia_editor::editor {
    using namespace omni::types;
    using namespace omniscia_editor::systems;
    using namespace omniscia_editor::windows;

    class Editor {
        private:
            /** Properties */
            bool _renderLevelPreviewWindow;
            bool _renderLevelPreviewHelpWindow;
            bool _renderHistroyWindow;
            bool _renderMetricsWindow;
            bool _renderTileGroupsManagementWindow;
            bool _renderSelectedTileGroupWindow;
            bool _renderAssetsViewWindow;
            bool _renderToolsWindow;
            bool _renderThemesWindow;

            bool _renderPropertiesWindow;

        public:
            friend class omni::reflector::FieldFriendlyScope;
            friend class omni::reflector::Reflection<Editor>;

            Editor() {
                _renderLevelPreviewWindow = true;
                _renderLevelPreviewHelpWindow = true;
                _renderHistroyWindow = true;
                _renderMetricsWindow = true;
                _renderTileGroupsManagementWindow = true;
                _renderSelectedTileGroupWindow = true;
                _renderAssetsViewWindow = true;
                _renderToolsWindow = true;
                _renderThemesWindow = false;

                _renderPropertiesWindow = false;

                ThemesWindow::get_instance().apply_default();   
            }

            void render() {
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

                if (ImGui::BeginMenuBar()) {
                    if (ImGui::BeginMenu("File")) {
                        if(ImGui::MenuItem("New", nullptr, nullptr)) {
                            LevelManager::get_instance().file_new();
                        };
                        ImGui::Separator();

                        if(ImGui::MenuItem("Open", nullptr, nullptr)) {
                            LevelManager::get_instance().file_open();
                        };

                        if(ImGui::MenuItem("Open Recent", nullptr, nullptr)) {
                            // evelManager::get_instance().file_new();
                        };
                        ImGui::Separator();

                        if(ImGui::MenuItem("Save", nullptr, nullptr)) {
                            LevelManager::get_instance().file_save();
                        };
                        ImGui::Separator();

                        if(ImGui::MenuItem("Exit", nullptr, nullptr)) {

                        };

                        ImGui::EndMenu();
                    }
                    if (ImGui::BeginMenu("View")) {
                        ImGui::MenuItem("Tools", nullptr,               &_renderToolsWindow);
                        ImGui::MenuItem("Level preview", nullptr,       &_renderLevelPreviewWindow);
                        ImGui::MenuItem("Level preview help", nullptr,  &_renderLevelPreviewHelpWindow);
                        ImGui::MenuItem("History", nullptr,             &_renderHistroyWindow);
                        ImGui::MenuItem("Assets view", nullptr,         &_renderAssetsViewWindow);
                        ImGui::MenuItem("Themes", nullptr,              &_renderThemesWindow);

                        ImGui::Separator();

                        if (ImGui::BeginMenu("Tile groups")) {
                            ImGui::MenuItem("Tile groups", nullptr,             &_renderTileGroupsManagementWindow);
                            ImGui::MenuItem("Selected tile group", nullptr,     &_renderSelectedTileGroupWindow);

                            ImGui::EndMenu();
                        }

                        if (ImGui::BeginMenu("Tile")) {
                            ImGui::MenuItem("Tile preview", nullptr, nullptr);
                            ImGui::MenuItem("Tile editor", nullptr, nullptr);

                            ImGui::EndMenu();
                        }
                        ImGui::Separator();

                        ImGui::MenuItem("Metrics", nullptr, &_renderMetricsWindow);

                        ImGui::EndMenu();
                    }
                    if (ImGui::MenuItem("Properties", nullptr, nullptr)) {
                        _renderPropertiesWindow = !_renderPropertiesWindow;
                    }

                    ImGui::EndMenuBar();
                }
                
                ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
                ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);

                if(_renderToolsWindow) ToolsWindow::get_instance().render_window();
                if(_renderSelectedTileGroupWindow) SelectedTileGroupWindow::get_instance().render_window();
                if(_renderTileGroupsManagementWindow) TileGroupsManagementWindow::get_instance().render_window();
                if(_renderLevelPreviewWindow) LevelPreviewWindow::get_instance().render_window();
                if(_renderLevelPreviewHelpWindow) LevelPreviewHelpWindow::get_instance().render_window();
                if(_renderHistroyWindow) HistoryWindow::get_instance().render_window();
                if(_renderMetricsWindow) MetricsWindow::get_instance().render_window();
                if(_renderAssetsViewWindow) AssetsViewWindow::get_instance().render_window();
                
                if(_renderThemesWindow) ThemesWindow::get_instance().render_window();
                if(_renderPropertiesWindow) PropertiesWindow::get_instance().render_window();

                // ImGui::ShowDemoWindow();

                ImGui::End();          
            };
        
        static Editor& get_instance() {
            static Editor editor;
            return editor;
        }
    };
}

template<>																	               
struct omni::reflector::Reflection<omniscia_editor::editor::Editor> {									               
    const constexpr static std::type_info &typeInfo = typeid(omniscia_editor::editor::Editor);           
    const constexpr static auto clearTypeName = "Editor";
    const constexpr static auto meta = std::make_tuple(
        omni::reflector::FieldFriendlyScope::field_registration(&omniscia_editor::editor::Editor::_renderLevelPreviewWindow, "Render level preview window"),
        omni::reflector::FieldFriendlyScope::field_registration(&omniscia_editor::editor::Editor::_renderLevelPreviewHelpWindow, "Render level preview help window"),
        omni::reflector::FieldFriendlyScope::field_registration(&omniscia_editor::editor::Editor::_renderHistroyWindow, "Render history window"),
        omni::reflector::FieldFriendlyScope::field_registration(&omniscia_editor::editor::Editor::_renderMetricsWindow, "Render metrics window"),
        omni::reflector::FieldFriendlyScope::field_registration(&omniscia_editor::editor::Editor::_renderTileGroupsManagementWindow, "Render tile groups management window"),
        omni::reflector::FieldFriendlyScope::field_registration(&omniscia_editor::editor::Editor::_renderSelectedTileGroupWindow, "Render selected tile group window"),
        omni::reflector::FieldFriendlyScope::field_registration(&omniscia_editor::editor::Editor::_renderAssetsViewWindow, "Render assets view window"),
        omni::reflector::FieldFriendlyScope::field_registration(&omniscia_editor::editor::Editor::_renderToolsWindow, "Render tools window"),

        omni::reflector::FieldFriendlyScope::field_registration(&omniscia_editor::editor::Editor::_renderPropertiesWindow, "Render properties window")
    );																		               
};

#endif
