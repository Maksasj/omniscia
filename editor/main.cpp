#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

int main(void) {
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(640, 480, "Omniscia Level Editor", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); 
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    bool tiles[20][20] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        auto flags = 
            ImGuiWindowFlags_NoTitleBar | 
            ImGuiWindowFlags_NoScrollbar | 
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoBringToFrontOnFocus | 
            ImGuiWindowFlags_NoMove;

        int sizeX; int sizeY;
        glfwGetWindowSize(window, &sizeX, &sizeY);
        ImGui::SetNextWindowSize({(float)sizeX, (float)sizeY});
        ImGui::Begin("Omniscia Editor", NULL, flags);
            ImGui::BeginTabBar("Omniscia Editor Tabs");
                if(ImGui::BeginTabItem("Level")) {;
                    if(ImGui::BeginChild("left pane", ImVec2(150, 0), true)) {
                        ImGui::EndChild();
                    }

                    ImGui::SameLine();

                    if(ImGui::BeginChild("right pane", ImVec2(0, 0), true)){
                        ImVec2 canvas_p0 = ImGui::GetCursorScreenPos();      // ImDrawList API uses screen coordinates!
                        ImVec2 canvas_sz = ImGui::GetContentRegionAvail();   // Resize canvas to what's available
                        if (canvas_sz.x < 50.0f) canvas_sz.x = 50.0f;
                        if (canvas_sz.y < 50.0f) canvas_sz.y = 50.0f;
                        ImVec2 canvas_p1 = ImVec2(canvas_p0.x + canvas_sz.x, canvas_p0.y + canvas_sz.y);

                        ImDrawList* draw_list = ImGui::GetWindowDrawList();
                        draw_list->PushClipRect(canvas_p0, canvas_p1, true);
                        draw_list->AddRectFilled(canvas_p0, canvas_p1, IM_COL32(25, 25, 25, 255));
                        for(int x = 0; x < 20; ++x) {
                            for(int y = 0; y < 20; ++y) {
                                if(!tiles[y][x]) continue;

                                int xStart = 100;
                                int yStart = 50;

                                draw_list->AddRectFilled({xStart + (float)x*50, yStart + (float)y*50}, {xStart + ((float)x + 1)*50, yStart + ((float)y + 1)*50}, IM_COL32(255, 255, 0, 255));
                            }
                        }
                        draw_list->PopClipRect();

                        ImGuiStyle& style = ImGui::GetStyle();
                        style.WindowBorderSize = 0.0f;

                        auto flags = 
                            ImGuiWindowFlags_NoTitleBar |
                            ImGuiWindowFlags_NoMove |
                            ImGuiWindowFlags_NoSavedSettings |
                            ImGuiWindowFlags_NoDecoration |
                            ImGuiWindowFlags_NoResize;

                        ImGui::SetNextWindowBgAlpha(0.0f); // Transparent background
                        ImGui::SetNextWindowPos({ImGui::GetWindowSize().x - 190, ImGui::GetWindowSize().y - 25});
                        if (ImGui::Begin("Example: Simple overlay", NULL, flags)) {
                            ImGui::Text("Application average %.3f [ms/frame] (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
                            if (ImGui::IsMousePosValid())
                                ImGui::Text("Mouse Position: (%.1f,%.1f)", io.MousePos.x, io.MousePos.y);
                            else
                                ImGui::Text("Mouse Position: <invalid>");
                            ImGui::End();
                        }

                        ImGui::EndChild();
                    }

                    ImGui::EndTabItem();
                }
            ImGui::EndTabBar();
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
