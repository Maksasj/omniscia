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

            AssetsViewWindow() {
                _managers.push_back({"Textures", &TextureManager::get_instance()});
            };

            void render_window() override {
                if(!ImGui::Begin("Assets view")) {
                    ImGui::End();
                    return;
                }

                const auto windowSize = ImGui::GetWindowSize();

                ImGui::BeginChild("ChildL", ImVec2(windowSize.x / 4.0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);
                    if (ImGui::BeginListBox("##listbox 3", ImVec2(-FLT_MIN, -FLT_MIN))) {
                        for (int n = 0; n < _managers.size(); n++) {
                            const bool isSelected = (selectedManagerId == n);
                            if (ImGui::Selectable(_managers[n]._label.c_str(), isSelected))
                                selectedManagerId = n;

                            if (isSelected)
                                ImGui::SetItemDefaultFocus();
                        }

                        ImGui::EndListBox();
                    }
                ImGui::EndChild();

                ImGui::SameLine();

                // ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
                ImGui::BeginChild("ChildR", ImVec2(-FLT_MIN, -FLT_MIN), true, ImGuiWindowFlags_None);

                ImGui::Text("%s", _managers[selectedManagerId]._label.c_str());

                AssetManager* activeManager = _managers[selectedManagerId]._manager; 

                if(ImGui::Button("Reaload assets")) {
                    activeManager->reload_assets("assets/texture_assets.json");
                }
                ImGui::SameLine();

                static bool assetPreview = true;

                ImGui::Checkbox("Asset preview", &assetPreview);
                activeManager->render_asset_preview(assetPreview);

                ImGui::EndChild();
                // ImGui::PopStyleVar();

                ImGui::End();
            }

            void render_properties() override {
                PropertiesFieldQuery::property_window_edit_query(*this);
            }

            static AssetsViewWindow& get_instance() {
                static AssetsViewWindow window;
                return window;
            }
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
