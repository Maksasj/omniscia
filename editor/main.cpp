#include "gfx.h"
#include "editor.h"

int main(void) {
    using namespace omni::types;
    using namespace omniscia_editor;
    using namespace omniscia_editor::editor;

    if(init_glfw())
        return 1;

    Window window;

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO(); 
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window.get_backend(), true);
    ImGui_ImplOpenGL3_Init("#version 330");

    ImFont* font = io.Fonts->AddFontFromFileTTF("assets\\fonts\\Nunito-Medium.ttf", 21);

    while (!glfwWindowShouldClose(window.get_backend())) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        Editor::get_instance().render();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());     

        glfwSwapBuffers(window.get_backend());
        glfwPollEvents();
    } 

    glfwTerminate();
    return 0;
}
