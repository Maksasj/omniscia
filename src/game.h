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
#include "crab.h"
#include "beachParallaxBackground.h"
#include "gfx.h"
#include "debug_ui.h"
#include "scene.h"
#include "scene_loader.h"

namespace omniscia {
    using namespace omniscia::core;
    using namespace omniscia::gfx;

    class Game {
        private:
            GLFWwindow* window;

            Scene* _activeScene;
            std::unordered_map<std::string, Scene*> _scenes;

            std::deque<Scene::SceneDynamic> _timeLine;
        public:
            int load();
            int run();

            void switch_scene(std::string sceneId);
            void switch_scene(Scene* scenePtr);

            static Game& get_instance() {
                static Game game;
                return game;
            }

            std::deque<Scene::SceneDynamic>& ref_time_line() {
                return _timeLine;
            }

            Scene* get_active_scene() {
                return _activeScene;
            }
    };
}

#endif
