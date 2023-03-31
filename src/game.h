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
            ECS_TilemapRendererSystem::get_instance().time_sync();
            ECS_SpriteSheetRendererSystem::get_instance().time_sync();
            ECS_SpriteRendererSystem::get_instance().time_sync();
            ECS_PlayerControllerSystem::get_instance().time_sync();
            ECS_SpriteAnimationSystem::get_instance().time_sync();
            ECS_AABBColliderSystem::get_instance().time_sync();
            ECS_2DPhysicsRigidbodySystem::get_instance().time_sync();
            ECS_GravitySystem::get_instance().time_sync();
            ECS_CameraFollowSystem::get_instance().time_sync();
            ECS_PlayerJumpSystem::get_instance().time_sync();
            ECS_PlayerDebugMetricsSystem::get_instance().time_sync();

            dynamicPart.player.time_sync();
            for(auto &e : dynamicPart.dynamicEntities)
                e.time_sync();

            for(auto &e : staticPart.staticEntities)
                e.time_sync();
        }
    };
}

#endif
