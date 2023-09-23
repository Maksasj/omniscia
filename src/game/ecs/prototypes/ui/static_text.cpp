#include "ecs/prototypes/ui/static_text.h"

omniscia::core::StaticText::StaticText(const StaticTextProp& prop) : Entity() {
    add<ECS_Positioned>(0.0f, 0.0f);
    add<ECS_Scaled>(1.0f, 1.0f);
    add<ECS_TextRenderer>(prop._fontId, prop._textToRender, prop._lineLetterSpacing, prop._rowLineSpacing, prop._charactersPerRow, 11);
}

omniscia::core::StaticText::StaticText(const Vec2f& position, const Vec2f& scale, const StaticTextProp& prop) : Entity() {
    add<ECS_Positioned>(position.x, position.y);
    add<ECS_Scaled>(scale.x, scale.y);
    add<ECS_TextRenderer>(prop._fontId, prop._textToRender, prop._lineLetterSpacing, prop._rowLineSpacing, prop._charactersPerRow, 11);
}