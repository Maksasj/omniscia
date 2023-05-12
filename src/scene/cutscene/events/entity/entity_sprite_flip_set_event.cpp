#include "entity_sprite_flip_set_event.h"
#include "game.h"

omniscia::core::CE_EntitySpriteFlipSetEvent::CE_EntitySpriteFlipSetEvent() {

}

omniscia::core::CE_EntitySpriteFlipSetEvent::CE_EntitySpriteFlipSetEvent(const CE_EntitySpriteFlipSetEvent&) {

}

void omniscia::core::CE_EntitySpriteFlipSetEvent::operator=(const CE_EntitySpriteFlipSetEvent&) {

}

omniscia::core::CE_EntitySpriteFlipSetEvent::CE_EntitySpriteFlipSetEvent(const CE_EntitySpriteFlipSetProp& data) : CE_EntitySpriteFlipSetProp(data), CE_Event(*(CE_Prop*)&data) {

}

void omniscia::core::CE_EntitySpriteFlipSetEvent::execute() {
    CutsceneDataPoolType* ptrParrentCutsceneDataPool = get_cutscene_data_pool();
    if(ptrParrentCutsceneDataPool == nullptr) 
        return;
    
    auto scene = Game::get_instance().get_active_scene();

    if(scene == nullptr) 
        return;
    
    CutsceneDataPoolType& _dataPool = *ptrParrentCutsceneDataPool;
    UUID* entityUUID = (UUID*)_dataPool[_entityTmpName].get();

    std::shared_ptr<Entity> entityPtr= scene->find_static_entity_by_uuid(*entityUUID);
    if(entityPtr == nullptr) return;

    ECS_Index<ECS_SpriteFlip> spriteFlipIndex = entityPtr->index<ECS_SpriteFlip>();
    
    if(!spriteFlipIndex.is_success()) 
        return;

    ECS_SpriteFlip& comp = entityPtr->ref_unsafe(spriteFlipIndex);

    comp.set_horizontal_flip(_horizontalFlip);
    comp.set_vertical_flip(_verticalFlip);
}
