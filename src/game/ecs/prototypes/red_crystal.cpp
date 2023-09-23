#include "ecs/prototypes/red_crystal.h"

omniscia::core::RedCrystal::RedCrystal(const Vec2f& position) : Entity() {
    add<ECS_Positioned>(position.x, position.y);
    add<ECS_Velocity>(
        Vec2f{0.002f, -0.002f}, 
        Vec2f{0.0035f, -0.0035f});
    add<ECS_PhysicsPositioned>();
    add<ECS_Acceleration>();
    add<ECS_Friction>();
    add<ECS_Scaled>(0.35f, 0.35f);
    add<ECS_SpriteFlip>(false, false);
    add<ECS_SpriteAnimationAuto>("red-crystal-idle-animation");
    add<ECS_SpriteSheetRenderer>("red-crystal-spritesheet", 0);
    add<ECS_Gravity>();
    add<ECS_BoxColliderMesh>(Vec2f{0.5f, 0.5f}, Vec2f{0.75f, 0.75f});
    add<ECS_MovableAABBCollider>(CollisionMask_None, CollisionMask_Tiles);
    add<ECS_2DPhysicsRigidbody>();

    add<ECS_TriggerAABBCollider>(CollisionMask_None, CollisionMask_Player);
    add<ECS_RedCrystalPopup>();
}
