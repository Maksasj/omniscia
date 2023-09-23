#include "scene/cutscene/events/entity/dynamic_entity_spriteanimation_set_animation_event.h"
#include "game.h"

omniscia::core::CE_DynamicEntitySpriteAnimationSetAnimationEvent::CE_DynamicEntitySpriteAnimationSetAnimationEvent() {

}

omniscia::core::CE_DynamicEntitySpriteAnimationSetAnimationEvent::CE_DynamicEntitySpriteAnimationSetAnimationEvent(const CE_DynamicEntitySpriteAnimationSetAnimationEvent&) {

}

void omniscia::core::CE_DynamicEntitySpriteAnimationSetAnimationEvent::operator=(const CE_DynamicEntitySpriteAnimationSetAnimationEvent&) {

}

omniscia::core::CE_DynamicEntitySpriteAnimationSetAnimationEvent::CE_DynamicEntitySpriteAnimationSetAnimationEvent(const CE_DynamicEntitySpriteAnimationSetAnimationProp& data) : CE_DynamicEntitySpriteAnimationSetAnimationProp(data), CE_Event(*(CE_Prop*)&data) {

}

void omniscia::core::CE_DynamicEntitySpriteAnimationSetAnimationEvent::execute() {
    CutsceneDataPoolType* ptrParrentCutsceneDataPool = get_cutscene_data_pool();
    if(ptrParrentCutsceneDataPool == nullptr) 
        return;
    
    auto scene = Game::get_instance().get_active_scene();

    if(scene == nullptr) 
        return;
    
    CutsceneDataPoolType& _dataPool = *ptrParrentCutsceneDataPool;
    UUID* entityUUID = (UUID*)_dataPool[_entityTmpName].get();

    std::shared_ptr<Entity> entityPtr= scene->find_dynamic_entity_by_uuid(*entityUUID);
    if(entityPtr == nullptr) return;

    ECS_Index<ECS_SpriteAnimation> spriteAnimationIndex = entityPtr->index<ECS_SpriteAnimation>();
    
    if(!spriteAnimationIndex.is_success()) 
        return;

    ECS_SpriteAnimation& comp = entityPtr->ref_unsafe(spriteAnimationIndex);

    comp.set_animation(_animationId);
    comp.reset_animation();
}
