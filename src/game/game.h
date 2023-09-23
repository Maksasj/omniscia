/**
 * @file 
 * game.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _GAME_H_
#define _GAME_H_

#include <deque>
#include <chrono>

#include "asset/texture/texture_manager.h"
#include "asset/animation/animation_manager.h"
#include "asset/level/level_asset_manager.h"
#include "ecs/ecs_components.h"
#include "gfx/render_stage_pool.h"
#include "properties.h"
#include "timesystem.h"
#include "controls.h"
#include "gfx/renderer.h"
#include "omni_types.tpp"
#include "gfx/sprite.h" 
#include "ecs/prototypes/player.h"
#include "ecs/prototypes/crab.h"
#include "ecs/prototypes/beachParallaxBackground.h"
#include "gfx/gfx.h"
#include "imgui/debug_info.h"
#include "scene/scene.h"
#include "scene/scene_loader/scene_loader.h"
#include "scene/scene_prototypes.h"
#include "scene/cutscene/cutscene_prototypes.h"
#include "gfx/monitor/monitor.h"
#include "gfx/instancing_sprite.h"

#include "imgui/debug_core.h"
#include "imgui/debug_metrics_window.h"
#include "imgui/debug_scene_manager_window.h"
#include "imgui/debug_rendering_stage_preview.h"

#include "asset/font/font_manager.h"
#include "asset/save/save_manager.h"

#include "sound/sound_fx.h"

#include "sound/sound_engine.h"
#include "asset/sound/sound_manager.h"
#include "sound/sound_speaker.h"
#include "sound/sound.h"

#include "timelessness_container.tpp"

namespace omniscia {
    using namespace omni::types;
    using namespace omniscia::core;
    using namespace omniscia::gfx;

    /**
     * @brief Game - main game classes, manages
     * all other classes, scenes, entities timeline,
     * rendering, everything. This is an entry point
     * of the game
    */
    class Game {
        private:
            /** @brief Pointer to GLFWwindow instance */
            GLFWwindow* window;

            /** @brief Pointer to the active scene */
            Scene* _activeScene = nullptr;
            /** @brief Pointer to the active cutscene */
            std::vector<Cutscene*> _activeCutscenes;

            /** @brief Container that stores pointers to cutscenes */
            std::unordered_map<std::string, Cutscene*> _cutscenes;

            /** @brief Container that stores pointers to scenes */
            std::unordered_map<std::string, Scene*> _scenes;

            /**  @brief Container that stores dynamic data of the active scene */
            TimeLessNessContainer<Scene::SceneDynamic, 5000> _timeLine; 

        public:
            /**
             * @brief Method used for loading gfx, sound engine, etc.
             * 
             * @return result 
            */
            void load();

            /**
             * @brief Runs game, can be runned only after loading game
             * 
             * @return result 
            */
            void run();

            /**
             * @brief Switches scene by scene id
             * 
             * @param sceneId scene id
            */
            void switch_scene(const std::string& sceneId);

            void start_cutscene(const std::string& cutsceneId);

            void start_cutscene(Cutscene* cutscenePtr);

            void update_cutscenes();

            void save_dynamic_checkpoint();

            void load_dynamic_checkpoint();

            /**
             * @brief Get singleton instance of the game class
             * 
             * @return Game& reference to the active game single ton
            */
            static Game& get_instance();

            /**
             * @brief Get reference to time line container
             * 
             * @return TimeLessNessContainer<Scene::SceneDynamic, 5000>& reference to the tile line container 
             */
            TimeLessNessContainer<Scene::SceneDynamic, 5000>& ref_time_line();

            /**
             * @brief Get the pointer to active scene
             * 
             * @return Scene* pointer to the active scene
            */
            Scene* get_active_scene();
    };
}

#endif
