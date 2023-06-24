#include "debug_scene_manager_window.h"
#include "game.h"

void omniscia::core::DebugSceneManagerWindow::render() {
    ImGuiIO& io = ImGui::GetIO();

    const DebugInfo& debugInfo = DebugInfo::get_instance();
    const auto& metrics = debugInfo._metrics;

    ImGuiWindowFlags window_flags = 
        ImGuiWindowFlags_AlwaysAutoResize | 
        ImGuiWindowFlags_NoSavedSettings | 
        ImGuiWindowFlags_NoFocusOnAppearing | 
        ImGuiWindowFlags_NoNav;

    Scene* activeScene = Game::get_instance().get_active_scene();
    if(activeScene == nullptr) return;

    ImGui::SetNextWindowBgAlpha(0.55f);
    if (ImGui::Begin("Scene manager", nullptr, window_flags)) {
        ImGui::Text("Dynamic entities");
        ImGui::Separator();
        for(const auto& entity : activeScene->dynamicPart.dynamicEntities) {
            if (ImGui::TreeNode(entity->get_uuid().to_string().c_str())) {
                auto& components = entity->_component_container._components;

                ImGui::Text("Component count %llu", components.size());


                for(auto& component : components) {
                    component->_type_query(nullptr);
                }

                ImGui::TreePop();
            }
        }

        ImGui::Text("Static entities");
        ImGui::Separator();
        for(const auto& entity : activeScene->staticPart.staticEntities) {
            if (ImGui::TreeNode(entity->get_uuid().to_string().c_str())) {
                auto& components = entity->_component_container._components;

                ImGui::Text("Component count %llu", components.size());

                for(auto& component : components) {
                    component->_type_query(nullptr);
                }

                ImGui::TreePop();
            }
        }
    }
    ImGui::End();
}

omniscia::core::DebugSceneManagerWindow& omniscia::core::DebugSceneManagerWindow::get_instance() {
    static DebugSceneManagerWindow instance;
    return instance;
}
