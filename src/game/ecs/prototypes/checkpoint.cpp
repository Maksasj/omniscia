#include "checkpoint.h"

omniscia::core::Checkpoint::Checkpoint(const Vec2f& position) : Entity() {
    add<ECS_Positioned>(position.x, position.y);
    add<ECS_Velocity>(
        Vec2f{0.002f, -0.002f}, 
        Vec2f{0.0035f, -0.0035f});
    add<ECS_PhysicsPositioned>();
    add<ECS_Acceleration>();
    add<ECS_Friction>();
    add<ECS_Scaled>(0.5f, 0.5f);
    add<ECS_SpriteFlip>(false, false);
    add<ECS_SpriteAnimationAuto>("checkpoint-animation");
    add<ECS_SpriteSheetRenderer>("checkpoint-spritesheet", 0);
    add<ECS_Gravity>();
    add<ECS_BoxColliderMesh>(Vec2f{0.5f, 0.5f}, Vec2f{0.95f, 0.95f});
    add<ECS_MovableAABBCollider>(CollisionMask_None, CollisionMask_Tiles);
    add<ECS_2DPhysicsRigidbody>();

    add<ECS_TriggerAABBCollider>(CollisionMask_None, CollisionMask_Player);
    add<ECS_CheckpointPopup>();
}
