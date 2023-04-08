#ifndef _LEVEL_H_
#define _LEVEL_H_

#include "types.tpp"
#include "player.h"
namespace omniscia::core {
    struct Level {
        struct LevelDynamic {
            Player player;
            std::vector<Entity> dynamicEntities;
        } dynamicPart;

        struct LevelStatic {
            std::vector<Entity> staticEntities;
        } staticPart;

        LevelDynamic clone() {
            std::vector<Entity> clonedDynamicEntities;
            for(auto& e : dynamicPart.dynamicEntities)
                clonedDynamicEntities.push_back(e.clone());

            return {dynamicPart.player.clone(), clonedDynamicEntities};
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
            ECS_StateMachineBaseSystem::get_instance().time_sync();

            dynamicPart.player.time_sync();
            for(auto &e : dynamicPart.dynamicEntities)
                e.time_sync();

            for(auto &e : staticPart.staticEntities)
                e.time_sync();
        }
    };
}

#endif
