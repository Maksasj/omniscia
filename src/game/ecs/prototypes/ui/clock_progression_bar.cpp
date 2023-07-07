#include "ecs/prototypes/ui/clock_progression_bar.h"

omniscia::core::ClockProgressionBar::ClockProgressionBar(const ClockProgressionBarProp& prop) : Entity() {
    add<ECS_Positioned>(prop._pos.x, prop._pos.y);
    add<ECS_Scaled>(prop._scale.x, prop._scale.y);
    add<ECS_SpriteFlip>(false, false);
    add<ECS_SpriteAnimationManual>(prop._animation);
    add<ECS_GuiSpriteSheetRenderer>(prop._texture, prop._layer);
    add<ECS_ClockProgressionBarController>();
}
