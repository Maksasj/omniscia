/**
 * @file 
 * debug_info.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _DEBUG_GUI_DEBUG_CORE_
#define _DEBUG_GUI_DEBUG_CORE_

#include <functional>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "omni_types.tpp"
#include "gfx.h"

namespace omniscia::core {
    using namespace omni::types;

    struct DebugCore {
        ImFont* font;

        void init(GLFWwindow* window) {
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGui::StyleColorsDark();
            ImGui_ImplGlfw_InitForOpenGL(window, true);
            ImGui_ImplOpenGL3_Init("#version 330");

            ImGuiIO& io = ImGui::GetIO();
            font = io.Fonts->AddFontFromFileTTF("assets\\fonts\\Nunito-Medium.ttf", 21);
        }

        DebugCore() {

        }

        static DebugCore& get_instance() {
            static DebugCore instance;
            return instance;
        }
    };
}

#endif
