#include "entity_spriterenderer_set_texture_event.h"
#include "game.h"

omniscia::core::CE_EntitySpriteRendererSetTextureEvent::CE_EntitySpriteRendererSetTextureEvent() {

}

omniscia::core::CE_EntitySpriteRendererSetTextureEvent::CE_EntitySpriteRendererSetTextureEvent(const CE_EntitySpriteRendererSetTextureEvent&) {

}

void omniscia::core::CE_EntitySpriteRendererSetTextureEvent::operator=(const CE_EntitySpriteRendererSetTextureEvent&) {

}

omniscia::core::CE_EntitySpriteRendererSetTextureEvent::CE_EntitySpriteRendererSetTextureEvent(const CE_EntitySpriteRendererSetTextureProp& data) : CE_EntitySpriteRendererSetTextureProp(data), CE_Event(*(CE_Prop*)&data) {

}

void omniscia::core::CE_EntitySpriteRendererSetTextureEvent::execute() {
    CutsceneDataPoolType* ptrParrentCutsceneDataPool = get_cutscene_data_pool();
    if(ptrParrentCutsceneDataPool == nullptr) 
        return;
    
    auto scene = Game::get_instance().get_active_scene();

    if(scene == nullptr) 
        return;
    
    CutsceneDataPoolType& _dataPool = *ptrParrentCutsceneDataPool;
    UUID* entityUUID = (UUID*)_dataPool[_entityTmpName].get();

    std::shared_ptr<Entity> entityPtr= scene->find_static_entity_by_uuid(*entityUUID);
    if(entityPtr.get() == nullptr) return;

    ECS_Index<ECS_SpriteRenderer> spriteRendererIndex = entityPtr->index<ECS_SpriteRenderer>();
    
    if(!spriteRendererIndex.is_success()) 
        return;

    ECS_SpriteRenderer& comp = entityPtr->ref_unsafe(spriteRendererIndex);

    comp.set_texture_by_id(_textureId);
}
