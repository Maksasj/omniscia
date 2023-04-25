#include "grandpa.h"

omniscia::core::Grandpa::Grandpa() {
    add<ECS_Positioned>(0.0f, 0.3f);
    add<ECS_Velocity>(
        Vec2f{0.002f, -0.002f}, 
        Vec2f{0.0035f, -0.0035f});
    add<ECS_PhysicsPositioned>();
    add<ECS_Acceleration>();
    add<ECS_Friction>();
    add<ECS_Scaled>(0.2f, 0.2f);
    add<ECS_SpriteFlip>(false, false);
    add<ECS_SpriteAnimation>("grandpa-idle-animation");
    add<ECS_SpriteSheetRenderer>("grandpa-spritesheet", 1);
    add<ECS_Gravity>();
    add<ECS_BoxColliderMesh>(Vec2f{0.5f, 0.5f}, Vec2f{1.0f, 0.5f});
    add<ECS_MovableAABBCollider>(CollisionMask_Player, CollisionMask_Tiles);
    add<ECS_2DPhysicsRigidbody>();
}
