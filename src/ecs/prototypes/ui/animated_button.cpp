#include "animated_button.h"

omniscia::core::AnimatedButton::AnimatedButton(const AnimatedButtonProp& prop) : Entity() {
    add<ECS_Positioned>(prop._pos.x, prop._pos.y);
    add<ECS_Scaled>(prop._scale.x, prop._scale.y);
    add<ECS_BoxColliderMesh>(prop._collider._xRanges, prop._collider._yRanges);
    add<ECS_SpriteAnimationManual>(prop._renderer._animation);
    add<ECS_GuiSpriteSheetRenderer>(prop._renderer._texture, prop._renderer._layer);
    add<ECS_Button>(prop._clickLambda, prop._hoverLambda, prop._unHoverLambda);
}
