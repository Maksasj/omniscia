#ifndef _GAME_H_
#define _GAME_H_

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <deque>
#include <chrono>

#include "types.tpp"
#include "render_stage.h"
#include "renderer.h"
#include "properties.h"
#include "texture_manager.h"
#include "animation_manager.h"
#include "sprite.h" 
#include "controls.h"
#include "player.h"
#include "timesystem.h"

namespace omniscia {
    using namespace omniscia::core;
    using namespace omniscia::renderer;

    class Game {
        private:
            GLFWwindow* window;

        public:
            int load();
            int run();
    };
}

#endif
