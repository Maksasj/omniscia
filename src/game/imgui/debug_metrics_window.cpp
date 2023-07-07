#include "debug_metrics_window.h"

void omniscia::core::DebugMetricsWindow::render() {
    ImGuiIO& io = ImGui::GetIO();

    const DebugInfo& debugInfo = DebugInfo::get_instance();
    const auto& metrics = debugInfo._metrics;

    ImGuiWindowFlags window_flags = 
        ImGuiWindowFlags_AlwaysAutoResize | 
        ImGuiWindowFlags_NoSavedSettings | 
        ImGuiWindowFlags_NoFocusOnAppearing | 
        ImGuiWindowFlags_NoNav;

    ImGui::SetNextWindowBgAlpha(0.55f);
    if (ImGui::Begin("Debug metrics", nullptr, window_flags)) {
        
        ImGui::Text("Frames buffered %llu / %llu", metrics._timeCurrentLineLength, metrics._timeMaxLineLength);
        ImGui::Text("Time manipulation time %f [ms]", metrics._timeManipulationTime);
        ImGui::Separator();

        ImGui::Text("Application average %.3f [ms/frame] (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        ImGui::Separator();
        
        ImGui::Text("Currently playing %d/64 [sounds]", metrics._currentlyPlayingSoundCount);
        ImGui::Separator();

        ImGui::Text("Player position: (x: %.3f, y: %.3f)", metrics._playerPos.x, metrics._playerPos.y);
        ImGui::Text("Camera position: (x: %.3f, y: %.3f)", metrics._cameraPos.x, metrics._cameraPos.y);

    }
    ImGui::End();
}

omniscia::core::DebugMetricsWindow& omniscia::core::DebugMetricsWindow::get_instance() {
    static DebugMetricsWindow instance;
    return instance;
}
