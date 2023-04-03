#ifndef _GAME_H_
#define _GAME_H_

#include <deque>
#include <chrono>

#include "texture_manager.h"
#include "animation_manager.h"
#include "ecs_components.h"
#include "render_stage.h"
#include "properties.h"
#include "timesystem.h"
#include "controls.h"
#include "renderer.h"
#include "types.tpp"
#include "sprite.h" 
#include "player.h"
#include "gfx.h"
#include "debug_ui.h"
#include "level.h"
#include "level_loader.h"

namespace omniscia {
    using namespace omniscia::core;
    using namespace omniscia::gfx;

    class Game {
        private:
            GLFWwindow* window;

        public:
            int load();
            int run();
    };
}

#endif
