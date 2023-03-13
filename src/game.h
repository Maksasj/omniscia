#ifndef _GAME_H_
#define _GAME_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "types.h"
#include "render_stage.h"
#include "renderer.h"
#include "properties.h"
#include "texture_manager.h"
#include "sprite.h" 
#include "controls.h"
#include "player.h"

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
