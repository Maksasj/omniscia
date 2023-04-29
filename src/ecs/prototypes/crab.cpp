#include "crab.h"

omniscia::core::Crab::Crab() : Entity() {
    add<ECS_Positioned>(0.3f, 1.3f);
    add<ECS_Velocity>(
        Vec2f{0.002f, -0.002f}, 
        Vec2f{0.0035f, -0.0035f});
    add<ECS_PhysicsPositioned>();
    add<ECS_Acceleration>();
    add<ECS_Friction>();
    add<ECS_Scaled>(0.1f, 0.1f);
    add<ECS_SpriteFlip>(false, false);
    add<ECS_SpriteAnimation>("crab-idle-animation");
    add<ECS_SpriteSheetRenderer>("crab-spritesheet", 0);
    add<ECS_Gravity>();
    add<ECS_SoundEmitter>();
    add<ECS_CrabController>();
    add<ECS_BoxColliderMesh>(Vec2f{0.5f, 0.5f}, Vec2f{0.9f, 0.5f});
    add<ECS_MovableAABBCollider>(CollisionMask_AmbientEntities, CollisionMask_Tiles);
    add<ECS_2DPhysicsRigidbody>();
}
