#include "find_static_entity_cutscene_event.h"
#include "game.h"

template<class _T>
omniscia::core::CE_FindStaticEntityEvent<_T>::CE_FindStaticEntityEvent() {

}

template<class _T>
omniscia::core::CE_FindStaticEntityEvent<_T>::CE_FindStaticEntityEvent(const CE_FindStaticEntityEvent&) {

}

template<class _T>
void omniscia::core::CE_FindStaticEntityEvent<_T>::operator=(const CE_FindStaticEntityEvent&) {

}

template<class _T>
omniscia::core::CE_FindStaticEntityEvent<_T>::CE_FindStaticEntityEvent(const CE_FindStaticEntityProp& data) : CE_FindStaticEntityProp(data), CE_Event(*(CE_Prop*)&data) {

}

template<class _T>
void omniscia::core::CE_FindStaticEntityEvent<_T>::execute() {
    CutsceneDataPoolType* ptrParrentCutsceneDataPool = get_cutscene_data_pool();
    if(ptrParrentCutsceneDataPool == nullptr) 
        return;
    
    Scene* scene = Game::get_instance().get_active_scene();

    if(scene == nullptr) 
        return;

    _T* entity = (_T*) scene->find_static_entity_by_prototype<_T>().get();

    if(entity == nullptr)
        return;

    CutsceneDataPoolType& _dataPool = *ptrParrentCutsceneDataPool;
    _dataPool[_entityTmpName] = std::make_shared<UUID>(entity->get_uuid());
}

template class omniscia::CE_FindStaticEntityEvent<omniscia::Player>;