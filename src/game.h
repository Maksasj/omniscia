#ifndef _GAME_H_
#define _GAME_H_

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <deque>
#include <chrono>

#include <thread>

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

#include "ecs_components.h"


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

    struct Level {
        struct LevelDynamic {
            Player player;
            std::vector<Entity> dynamicEntities;
        } dynamicPart;

        struct LevelStatic {
            std::vector<Entity> staticEntities;
        } staticPart;

        LevelDynamic clone() {
            return {dynamicPart.player.clone(), dynamicPart.dynamicEntities};
        }

        void time_sync() {
            ECS_SpriteSheetRendererSystem::get_instance().time_sync();
            ECS_SpriteRendererSystem::get_instance().time_sync();
            ECS_PlayerControllerSystem::get_instance().time_sync();
            ECS_SpriteAnimationSystem::get_instance().time_sync();
            ECS_AABBColliderSystem::get_instance().time_sync();
            ECS_2DPhysicsRigidbodySystem::get_instance().time_sync();
            ECS_GravitySystem::get_instance().time_sync();
            ECS_CameraFollowSystem::get_instance().time_sync();
            ECS_PlayerJumpSystem::get_instance().time_sync();

            dynamicPart.player.time_sync();
            for(auto &e : dynamicPart.dynamicEntities)
                e.time_sync();

            for(auto &e : staticPart.staticEntities)
                e.time_sync();
        }
    };
}

#endif
