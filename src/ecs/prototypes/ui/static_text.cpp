#include "static_text.h"

omniscia::core::StaticText::StaticText(const StaticTextProp& prop) {
    add<ECS_Positioned>(0.0f, 0.0f);
    add<ECS_Scaled>(1.0f, 1.0f);
    add<ECS_TextRenderer>(prop._fontId, prop._textToRender, prop._lineLetterSpacing, prop._rowLineSpacing, prop._charactersPerRow, 1);
}

omniscia::core::StaticText::StaticText(const Vec2f& pos, const Vec2f& scale, const StaticTextProp& prop) {
    add<ECS_Positioned>(pos.x, pos.y);
    add<ECS_Scaled>(scale.x, scale.y);
    add<ECS_TextRenderer>(prop._fontId, prop._textToRender, prop._lineLetterSpacing, prop._rowLineSpacing, prop._charactersPerRow, 1);
}