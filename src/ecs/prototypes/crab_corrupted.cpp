#include "crab_corrupted.h"

omniscia::core::CrabCorrupted::CrabCorrupted(const Vec2f& position) : Entity() {
    add<ECS_Positioned>(position.x, position.y);
    add<ECS_Velocity>(
        Vec2f{0.002f, -0.002f}, 
        Vec2f{0.0035f, -0.0035f});
    add<ECS_PhysicsPositioned>();
    add<ECS_Acceleration>();
    add<ECS_Friction>();
    add<ECS_Scaled>(0.2f, 0.2f);
    add<ECS_SpriteFlip>(false, false);
    add<ECS_SpriteAnimationAuto>("crab-idle-animation");
    add<ECS_SpriteSheetRenderer>("crab-corrupted-spritesheet", 0);
    add<ECS_Gravity>();
    add<ECS_SoundEmitter>();
    add<ECS_CrabController>();
    add<ECS_BoxColliderMesh>(Vec2f{0.5f, 0.5f}, Vec2f{0.9f, 0.5f});
    add<ECS_MovableAABBCollider>(CollisionMask_AmbientEntities, CollisionMask_Tiles);
    add<ECS_Deadly>();
    add<ECS_2DPhysicsRigidbody>();
}
