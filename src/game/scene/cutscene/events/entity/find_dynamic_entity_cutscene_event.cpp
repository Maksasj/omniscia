#include "find_dynamic_entity_cutscene_event.h"
#include "game.h"

template<class _T>
omniscia::core::CE_FindDynamicEntityEvent<_T>::CE_FindDynamicEntityEvent() {

}

template<class _T>
omniscia::core::CE_FindDynamicEntityEvent<_T>::CE_FindDynamicEntityEvent(const CE_FindDynamicEntityEvent&) {

}

template<class _T>
void omniscia::core::CE_FindDynamicEntityEvent<_T>::operator=(const CE_FindDynamicEntityEvent&) {

}

template<class _T>
omniscia::core::CE_FindDynamicEntityEvent<_T>::CE_FindDynamicEntityEvent(const CE_IndexDynamicEntityProp& data) : CE_IndexDynamicEntityProp(data), CE_Event(*(CE_Prop*)&data) {

}

template<class _T>
void omniscia::core::CE_FindDynamicEntityEvent<_T>::execute() {
    CutsceneDataPoolType* ptrParrentCutsceneDataPool = get_cutscene_data_pool();
    if(ptrParrentCutsceneDataPool == nullptr) 
        return;
    
    Scene* scene = Game::get_instance().get_active_scene();

    if(scene == nullptr) 
        return;

    _T* entity = (_T*) scene->find_dynamic_entity_by_prototype<_T>().get();

    if(entity == nullptr)
        return;

    CutsceneDataPoolType& _dataPool = *ptrParrentCutsceneDataPool;
    _dataPool[_entityTmpName] = std::make_shared<UUID>(entity->get_uuid());
}

// template class omniscia::CE_FindDynamicEntityEvent<omniscia::Player>;