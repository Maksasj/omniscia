#include "collected_text.h"

omniscia::core::CollectedText::CollectedText(const CollectedTextProp& prop) : Entity() {
    add<ECS_Positioned>(0.0f, 0.0f);
    add<ECS_Scaled>(1.0f, 1.0f);
    add<ECS_TextRenderer>(prop._fontId, prop._textToRender, prop._lineLetterSpacing, prop._rowLineSpacing, prop._charactersPerRow, 11);
}

omniscia::core::CollectedText::CollectedText(const Vec2f& position, const Vec2f& scale, const CollectedTextProp& prop) : Entity() {
    add<ECS_Positioned>(position.x, position.y);
    add<ECS_Scaled>(scale.x, scale.y);
    add<ECS_TextRenderer>(prop._fontId, prop._textToRender, prop._lineLetterSpacing, prop._rowLineSpacing, prop._charactersPerRow, 11);
}