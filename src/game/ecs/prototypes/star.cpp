#include "ecs/prototypes/star.h"

omniscia::core::Star::Star(const Vec2f& position) : Entity() {
    add<ECS_Positioned>(position.x, position.y);
        add<ECS_Velocity>(
        Vec2f{0.002f, -0.002f}, 
        Vec2f{0.0035f, -0.0035f});
    add<ECS_PhysicsPositioned>();
    add<ECS_Acceleration>();
    add<ECS_Friction>();

    add<ECS_Scaled>(0.1f, 0.1f);
    add<ECS_SpriteFlip>(false, false);
    add<ECS_Transparency>(1.0f);
    add<ECS_SpriteAnimationAuto>("star-spinning-animation");
    add<ECS_SpriteSheetRenderer>("star-spritesheet", 0);
    add<ECS_BoxColliderMesh>(Vec2f{0.5f, 0.5f}, Vec2f{0.5f, 0.5f});
    add<ECS_TriggerAABBCollider>(CollisionMask_None, CollisionMask_Player);
    add<ECS_Collectable>();
    add<ECS_MovableAABBCollider>(CollisionMask_AmbientEntities, CollisionMask_Tiles);
    add<ECS_2DPhysicsRigidbody>();
    
    add<ECS_StarController>();
}
