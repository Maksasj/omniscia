#include "scene/cutscene/events/entity/static_entity_spriteanimation_set_animation_event.h"
#include "game.h"

omniscia::core::CE_StaticEntitySpriteAnimationSetAnimationEvent::CE_StaticEntitySpriteAnimationSetAnimationEvent() {

}

omniscia::core::CE_StaticEntitySpriteAnimationSetAnimationEvent::CE_StaticEntitySpriteAnimationSetAnimationEvent(const CE_StaticEntitySpriteAnimationSetAnimationEvent&) {

}

void omniscia::core::CE_StaticEntitySpriteAnimationSetAnimationEvent::operator=(const CE_StaticEntitySpriteAnimationSetAnimationEvent&) {

}

omniscia::core::CE_StaticEntitySpriteAnimationSetAnimationEvent::CE_StaticEntitySpriteAnimationSetAnimationEvent(const CE_StaticEntitySpriteAnimationSetAnimationProp& data) : CE_StaticEntitySpriteAnimationSetAnimationProp(data), CE_Event(*(CE_Prop*)&data) {

}

void omniscia::core::CE_StaticEntitySpriteAnimationSetAnimationEvent::execute() {
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

    ECS_Index<ECS_SpriteAnimation> spriteAnimationIndex = entityPtr->index<ECS_SpriteAnimation>();
    
    if(!spriteAnimationIndex.is_success()) 
        return;

    ECS_SpriteAnimation& comp = entityPtr->ref_unsafe(spriteAnimationIndex);

    comp.set_animation(_animationId);
    comp.reset_animation();
}
