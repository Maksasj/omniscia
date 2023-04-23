#include "letterbox_cutscene_event.h"

omniscia::core::CE_LetterBoxEvent::CE_LetterBoxEvent() {

}

omniscia::core::CE_LetterBoxEvent::CE_LetterBoxEvent(const CE_LetterBoxEvent&) {

}

void omniscia::core::CE_LetterBoxEvent::operator=(const CE_LetterBoxEvent&) {

}

omniscia::core::CE_LetterBoxEvent::CE_LetterBoxEvent(const auto& data) : CE_LetterBoxProp(data), CE_Event(*(CE_Prop*)&data) {
    bottomBox.add<ECS_ParallaxSpriteRendererFront>("factorio_girl_texture", 1, [](f32& layerOffset) { return 0; });
    upperBox.add<ECS_ParallaxSpriteRendererFront>("factorio_girl_texture", 1, [](f32& layerOffset) { return 0; });
}

void omniscia::core::CE_LetterBoxEvent::execute() {
    static u64 t = 0;

    if(t == 0) {
        bottomBox.time_sync();
        upperBox.time_sync();
    }

    ++t;
}
