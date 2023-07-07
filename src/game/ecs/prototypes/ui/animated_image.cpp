#include "animated_image.h"

omniscia::core::AnimatedImage::AnimatedImage(const AnimatedImageProp& prop) : Entity() {
    add<ECS_Positioned>(prop._pos.x, prop._pos.y);
    add<ECS_Scaled>(prop._scale.x, prop._scale.y);
    add<ECS_SpriteFlip>(false, false);
    add<ECS_SpriteAnimationAuto>(prop._animation);
    add<ECS_GuiSpriteSheetRenderer>(prop._texture, prop._layer);
}
