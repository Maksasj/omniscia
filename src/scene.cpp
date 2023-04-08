#include "scene.h"

omniscia::core::Scene::SceneDynamic omniscia::core::Scene::clone() {
    std::vector<Entity> clonedDynamicEntities;
    for(auto& e : dynamicPart.dynamicEntities)
        clonedDynamicEntities.push_back(e.clone());

    return {clonedDynamicEntities};
}

void omniscia::core::Scene::unbind() {
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
    ECS_ParallaxSpriteRendererBackSystem::get_instance().time_sync();
    ECS_ParallaxSpriteRendererFrontSystem::get_instance().time_sync();
}

void omniscia::core::Scene::time_sync() {
    unbind();

    for(auto &e : dynamicPart.dynamicEntities)
        e.time_sync();

    for(auto &e : staticPart.staticEntities)
        e.time_sync();
}

omniscia::core::Scene::SceneDynamic& omniscia::core::Scene::ref_dynamic_part() {
    return dynamicPart;
}

omniscia::core::Scene::SceneStatic& omniscia::core::Scene::ref_static_part() {
    return staticPart;
}
