#include "index_dynamic_entity_cutscene_event.h"
#include "game.h"

template<class _T>
omniscia::core::CE_IndexDynamicEntityEvent<_T>::CE_IndexDynamicEntityEvent() {

}

template<class _T>
omniscia::core::CE_IndexDynamicEntityEvent<_T>::CE_IndexDynamicEntityEvent(const CE_IndexDynamicEntityEvent&) {

}

template<class _T>
void omniscia::core::CE_IndexDynamicEntityEvent<_T>::operator=(const CE_IndexDynamicEntityEvent&) {

}

template<class _T>
omniscia::core::CE_IndexDynamicEntityEvent<_T>::CE_IndexDynamicEntityEvent(const CE_IndexDynamicEntityProp& data) : CE_IndexDynamicEntityProp(data), CE_Event(*(CE_Prop*)&data) {

}

template<class _T>
void omniscia::core::CE_IndexDynamicEntityEvent<_T>::execute() {
    CutsceneDataPoolType* ptrParrentCutsceneDataPool = get_cutscene_data_pool();
    if(ptrParrentCutsceneDataPool == nullptr) 
        return;
    
    Scene* scene = Game::get_instance().get_active_scene();

    if(scene == nullptr) 
        return;

    _T* entity = scene->get_dynamic_entity_by_prototype<_T>();
    
    if(entity == nullptr)
        return;

    CutsceneDataPoolType& _dataPool = *ptrParrentCutsceneDataPool;
    _dataPool[_entityTmpName] = std::make_shared<UUID>(entity->get_uuid());
}

template class omniscia::CE_IndexDynamicEntityEvent<omniscia::Player>;