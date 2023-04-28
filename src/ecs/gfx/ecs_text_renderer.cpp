#include "ecs_text_renderer.h"

omniscia::core::ecs::ECS_TextRenderer::ECS_TextRenderer(const std::string& fontId, const std::string& textToRender, const f32& lineLetterSpacing, const f32& rowLineSpacing, const u64& charactersPerRow, const u32& layer) 
        : ECS_InstancingRenderer(fontId, layer) {

    _fontAsset = &FontManager::get_instance().get(fontId);

    _lineLetterSpacing = lineLetterSpacing;
    _rowLineSpacing = rowLineSpacing;
    _charactersPerRow = charactersPerRow;

    set_text_to_render(textToRender, _lineLetterSpacing, _rowLineSpacing, _charactersPerRow);
}

void omniscia::core::ecs::ECS_TextRenderer::reindex(void* parent) {
    ECS_InstancingRenderer::reindex(parent);

    set_text_to_render(_textToRender, _lineLetterSpacing, _rowLineSpacing, _charactersPerRow);
}

void omniscia::core::ecs::ECS_TextRenderer::set_text_to_render(const std::string& textToRender, const f32& lineLetterSpacing, const f32& rowLineSpacing, const u64& charactersPerRow) {
    if(_fontAsset == nullptr) 
        return; 
    
    Vec2f scaleFactor = Vec2f{1.0f, 1.0f};
    if(_scaleIndex.is_success()) {
        ECS_Scaled& scaleComp = _parent->ref_unsafe(_scaleIndex);
        scaleFactor = scaleComp.get_scale();
    } 

    _textToRender = textToRender;

    _instancingData.clear();

    FontAssetProp& font = *_fontAsset->get_asset();

    f32 xOffset = 0.0f;
    f32 anothetXOffset = 0.0f;
    f32 yOffset = 0.0f;

    for(i32 i = 1; i < _textToRender.size(); ++i) {
        const i8& letter = _textToRender[i - 1];
        const i32 index = letter - font._startCharacter; 

        const i32 row =     (index % font._charactersPerRow);
        const i32 collum =  (index + font._charactersPerRow) / (font._charactersPerRow);
        
        _instancingData.push_back({
            Vec2f{xOffset, yOffset},
            Vec2f{1.0f, 1.0f},
            font._frameSize,
            Vec2f{row * font._frameSize.x, 1.0f - collum * font._frameSize.y}
        });

        xOffset += lineLetterSpacing * scaleFactor.x * 2;

        if(i % charactersPerRow == 0) {
            yOffset -= rowLineSpacing * scaleFactor.x * 2;
            xOffset = 0.0f;
        }
    }
}