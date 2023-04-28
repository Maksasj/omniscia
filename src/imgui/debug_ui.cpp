#include "debug_ui.h"

void omniscia::core::DebugUI::init(GLFWwindow* window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); 

    _imgui_io = &io;
    
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void omniscia::core::DebugUI::render() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    if(_imgui_io == nullptr) return;
    ImGuiIO& io = *_imgui_io;

    /* ImGui */
    ImGuiWindowFlags window_flags = 
        ImGuiWindowFlags_NoDecoration | 
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_AlwaysAutoResize | 
        ImGuiWindowFlags_NoSavedSettings | 
        ImGuiWindowFlags_NoFocusOnAppearing | 
        ImGuiWindowFlags_NoNav;

    ImGui::SetNextWindowPos({10.0f, 10.0f}, 0, {0.0f, 0.0f});
    ImGui::SetNextWindowBgAlpha(0.35f);
    ImGui::SetNextWindowSize({350.0f, 110.0f});
    if (ImGui::Begin("Example: Simple overlay", nullptr, window_flags)) {
        
        ImGui::Text("Frames buffered %llu / %llu", _metrics._timeCurrentLineLength, _metrics._timeMaxLineLength);
        ImGui::Text("Time manipulation time %f [ms]", _metrics._timeManipulationTime);
        ImGui::Separator();

        ImGui::Text("Application average %.3f [ms/frame] (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        ImGui::Separator();
        
        ImGui::Text("Currently playing %d/64 [sounds]", _metrics._currentlyPlayingSoundCount);
        ImGui::Separator();

        ImGui::Text("Player position: (x: %.3f, y: %.3f)", _metrics._playerPos.x, _metrics._playerPos.y);
        ImGui::Separator();

        ImGui::End();
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

omniscia::core::DebugUI::DebugMetrics& omniscia::core::DebugUI::get_metrics() {
    return _metrics;
};

omniscia::core::DebugUI& omniscia::core::DebugUI::get_instance() {
    static DebugUI instance;
    return instance;
}
