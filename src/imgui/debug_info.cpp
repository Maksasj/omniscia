#include "debug_info.h"

void omniscia::core::DebugInfo::init(GLFWwindow* window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); 

    _imgui_io = &io;
    
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

omniscia::core::DebugInfo::DebugMetrics& omniscia::core::DebugInfo::get_metrics() {
    return _metrics;
};

omniscia::core::DebugInfo& omniscia::core::DebugInfo::get_instance() {
    static DebugInfo instance;
    return instance;
}
