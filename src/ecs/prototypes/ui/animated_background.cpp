#include "animated_background.h"

omniscia::core::AnimatedBackground::AnimatedBackground() : Entity() {
    add<ECS_SpriteRenderer>("menu_background", 0);
}

omniscia::core::AnimatedBackground::AnimatedBackground(const AnimatedBackgroundProp& prop) : Entity() {
    add<ECS_SpriteAnimationAuto>(prop._animation);
    add<ECS_SpriteSheetRenderer>(prop._texture, prop._layer);
}
