#include "scene.h"

omniscia::core::Scene::SceneDynamic omniscia::core::Scene::clone() {
    std::vector<std::shared_ptr<Entity>> clonedDynamicEntities;
    for(auto& e : dynamicPart.dynamicEntities)
        clonedDynamicEntities.push_back(e->clone());

    return {clonedDynamicEntities};
}

omniscia::core::Scene::SceneStatic omniscia::core::Scene::clone_static() {
    std::vector<std::shared_ptr<Entity>> clonedStaticEntities;
    for(auto& e : staticPart.staticEntities)
        clonedStaticEntities.push_back(e->clone());

    return {clonedStaticEntities};
}

void omniscia::core::Scene::unbind() {
    ECS_PlayerControllerSystem::get_instance().time_sync();
    ECS_SpriteAnimationSystem::get_instance().time_sync();
    ECS_AABBColliderSystem::get_instance().time_sync();
    ECS_2DPhysicsRigidbodySystem::get_instance().time_sync();
    ECS_GravitySystem::get_instance().time_sync();
    ECS_CameraFollowSystem::get_instance().time_sync();
    ECS_PlayerJumpSystem::get_instance().time_sync();
    ECS_PlayerDebugMetricsSystem::get_instance().time_sync();
    ECS_StateMachineBaseSystem::get_instance().time_sync();
    ECS_SoundEmitterSystem::get_instance().time_sync();
    ECS_PlayerTimeJumpControllerSystem::get_instance().time_sync();
    ECS_ProRendererSystem::get_instance().time_sync();
    ECS_ButtonSystem::get_instance().time_sync();
    ECS_InteractiveSystem::get_instance().time_sync();
    ECS_DeadlySystem::get_instance().time_sync();
}

void omniscia::core::Scene::time_sync() {
    unbind();

    for(auto &e : dynamicPart.dynamicEntities)
        e->time_sync();

    for(auto &e : staticPart.staticEntities)
        e->time_sync();
}

omniscia::core::Scene::SceneDynamic& omniscia::core::Scene::ref_dynamic_part() {
    return dynamicPart;
}

omniscia::core::Scene::SceneDynamic& omniscia::core::Scene::ref_dynamic_checkpoint_part() {
    return checkpointDynamicPart;
}

omniscia::core::Scene::SceneStatic& omniscia::core::Scene::ref_static_part() {
    return staticPart;
}

void omniscia::core::Scene::load_checkpoint() {
    dynamicPart.dynamicEntities.clear();
    staticPart.staticEntities.clear();

    for(auto& e : checkpointStaticPart.staticEntities)
        staticPart.staticEntities.push_back(e->clone());

    for(auto& e : checkpointDynamicPart.dynamicEntities)
        dynamicPart.dynamicEntities.push_back(e->clone());
    
    // Todo resolve this cringe
    DebugUI::get_instance().get_metrics()._isTimeJump = true;

    time_sync();
}

void omniscia::core::Scene::save_checkpoint() {
    checkpointDynamicPart = clone();
    checkpointStaticPart = clone_static();
}
