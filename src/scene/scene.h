/**
 * @file 
 * scene.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _SCENE_H_
#define _SCENE_H_

#include "types.tpp"
#include "player.h"
#include "grandpa.h"

#include "debug_ui.h"
#include "markergroup_data_serializable.h"

#include "cutscene.h"

namespace omniscia::core {
    using namespace omni::types;
    using namespace omni::serializer;
    
    /**
     * @brief Class that manages all scene data, dynamic and static part
    */
    class Scene {
        public:
            /**
             * @brief SceneDynamic - class that used for storing 
             * and managing all dynamic entities
            */
            struct SceneDynamic {
                std::vector<std::shared_ptr<Entity>> dynamicEntities;
            };

            /**
             * @brief SceneStatic - class that used for storing 
             * and managing all static entities
            */
            struct SceneStatic {
                std::vector<std::shared_ptr<Entity>> staticEntities;
            };

        protected:
            /**
             * @brief Instance of the SceneDynamic
            */
            SceneDynamic dynamicPart;
            
            /**
             * @brief Instance of the SceneStatic
            */
            SceneStatic staticPart;

            /**
             * @brief Checkpoint part
            */
            SceneDynamic checkpointDynamicPart;
            SceneStatic checkpointStaticPart;

            SerializableVector<SerializableMarkerGroupData> _markerGroups;

        public:
            friend class SceneLoader;

            /**
             * @brief Method used for cloning dynamic scene part
             * 
             * @return SceneDynamic new dynamic scene part instance
            */
            SceneDynamic clone();

            SceneStatic clone_static();

            void load_checkpoint();

            void save_checkpoint();

            /**
             * @brief Unbinds all components from all systems
            */
            void unbind();

            /**
             * @brief Binds all components to systems
            */
            void time_sync();

            /**
             * @brief Get reference to scene dynamic part
             * 
             * @return SceneDynamic& reference to dynamic scene part
            */
            SceneDynamic& ref_dynamic_part();

            SceneDynamic& ref_dynamic_checkpoint_part();
            /**
             * @brief Get reference to scene static part
             * 
             * @return SceneStatic& reference to static scene part
            */
            SceneStatic& ref_static_part();

            /**
             * @brief Adds entity as dynamic entity
             * 
             * @tparam T type of the entity
             * 
             * @return UUID entities uuid
            */
            template<class T>
            UUID add_dynamic_entity() {
                auto& entities = dynamicPart.dynamicEntities; 
                entities.push_back(std::make_shared<T>());

                std::shared_ptr<Entity> entity = entities[entities.size() - 1];
                entity->set_time_type(EntityTimeType::DYNAMIC);

                return entity->get_uuid();
            }

            /**
             * @brief Adds entity as dynamic entity
             * 
             * @tparam T type of the entity
             * @tparam Args type of the entity constructor arguments
             * @param args entity constructor arguments
             * 
             * @return UUID entities uuid
            */
            template<class T, class... Args>
            UUID add_dynamic_entity(Args&&... args) {
                auto& entities = dynamicPart.dynamicEntities; 
                entities.push_back(std::make_shared<T>(std::forward<Args>(args)...));

                std::shared_ptr<Entity> entity = entities[entities.size() - 1];
                entity->set_time_type(EntityTimeType::DYNAMIC);

                return entity->get_uuid();
            }

            /**
             * @brief Adds entity as static entity
             * 
             * @tparam T type of the entity
             * 
             * @return UUID entities uuid
            */
            template<class T>
            UUID add_static_entity() {
                auto& entities = staticPart.staticEntities; 
                entities.push_back(std::make_shared<T>());

                std::shared_ptr<Entity> entity = entities[entities.size() - 1];
                entity->set_time_type(EntityTimeType::STATIC);

                return entity->get_uuid();
            }

            /**
             * @brief Adds entity as static entity
             * 
             * @tparam T type of the entity
             * @tparam Args type of the entity constructor arguments
             * @param args entity constructor arguments
             * 
             * @return UUID entities uuid
            */
            template<class T, class... Args>
            UUID add_static_entity(Args&&... args) {
                auto& entities = staticPart.staticEntities; 
                entities.push_back(std::make_shared<T>(std::forward<Args>(args)...));

                std::shared_ptr<Entity> entity = entities[entities.size() - 1];
                entity->set_time_type(EntityTimeType::STATIC);

                return entity->get_uuid();
            }

            template<class T>
            void summon_dynamic_entity_at_marker_group(const i32& markerGroupIndex) {
                SerializableMarkerGroupData& markerGroup = _markerGroups.get().at(markerGroupIndex);
                auto& entities = dynamicPart.dynamicEntities; 

                for(SerializableMarkerData& marker : markerGroup._markers.get()) {
                    entities.push_back(std::make_shared<T>(Vec2f{marker._position.get().x, marker._position.get().y}));

                    std::shared_ptr<Entity> entity = entities[entities.size() - 1];
                    entity->set_time_type(EntityTimeType::DYNAMIC);
                }
            }

            template<class T, class... Args>
            void summon_dynamic_entity_at_marker_group(const i32& markerGroupIndex, Args&&... args) {
                SerializableMarkerGroupData& markerGroup = _markerGroups.get().at(markerGroupIndex);
                auto& entities = dynamicPart.dynamicEntities; 

                for(SerializableMarkerData& marker : markerGroup._markers.get()) {
                    entities.push_back(std::make_shared<T>(Vec2f{marker._position.get().x, marker._position.get().y}, std::forward<Args>(args)...));
                    
                    std::shared_ptr<Entity> entity = entities[entities.size() - 1];
                    entity->set_time_type(EntityTimeType::DYNAMIC);
                }
            }

            template<class T>
            void summon_static_entity_at_marker_group(const i32& markerGroupIndex) {
                SerializableMarkerGroupData& markerGroup = _markerGroups.get().at(markerGroupIndex);
                auto& entities = staticPart.staticEntities; 

                for(SerializableMarkerData& marker : markerGroup._markers.get()) {
                    entities.push_back(std::make_shared<T>(Vec2f{marker._position.get().x, marker._position.get().y}));
       
                    std::shared_ptr<Entity> entity = entities[entities.size() - 1];
                    entity->set_time_type(EntityTimeType::STATIC);
                }
            }

            template<class T, class... Args>
            void summon_static_entity_at_marker_group(const i32& markerGroupIndex, Args&&... args) {
                SerializableMarkerGroupData& markerGroup = _markerGroups.get().at(markerGroupIndex);
                auto& entities = staticPart.staticEntities; 

                for(SerializableMarkerData& marker : markerGroup._markers.get()) {
                    entities.push_back(std::make_shared<T>(Vec2f{marker._position.get().x, marker._position.get().y}, std::forward<Args>(args)...));

                    std::shared_ptr<Entity> entity = entities[entities.size() - 1];
                    entity->set_time_type(EntityTimeType::STATIC);
                }
            }

            template<class Predicate>
            std::shared_ptr<omniscia::core::Entity> find_dynamic_entity_with_predicate(const Predicate& predicate) {
                auto& entities = dynamicPart.dynamicEntities;

                for(std::shared_ptr<omniscia::core::Entity>& ptr : entities) {
                    if(predicate(ptr)) {
                        return ptr;
                    }
                }

                return nullptr;
            }

            template<class Predicate>
            std::shared_ptr<omniscia::core::Entity> find_static_entity_with_predicate(const Predicate& predicate) {
                auto& entities = staticPart.staticEntities;

                for(std::shared_ptr<omniscia::core::Entity>& ptr : entities) {
                    if(predicate(ptr))
                        return ptr;
                }

                return nullptr;
            }

            inline std::shared_ptr<Entity> find_dynamic_entity_by_uuid(const UUID& uuid) {
                return find_dynamic_entity_with_predicate(Predicate_EntityUUIDEqual(uuid));
            }
    
            inline std::shared_ptr<Entity> find_static_entity_by_uuid(const UUID& uuid) {
                return find_static_entity_with_predicate(Predicate_EntityUUIDEqual(uuid));
            }
            
            template<class _T>
            inline std::shared_ptr<omniscia::core::Entity> find_dynamic_entity_by_prototype() {
                return find_dynamic_entity_with_predicate(Predicate_EntityPrototypeEqual<_T>());
            }

            template<class _T>
            inline std::shared_ptr<omniscia::core::Entity> find_static_entity_by_prototype() {
                return find_static_entity_with_predicate(Predicate_EntityPrototypeEqual<_T>());
            }
            
            template<class Predicate>
            std::vector<std::shared_ptr<omniscia::core::Entity>> find_dynamic_entities_with_predicate(const Predicate& predicate) {
                auto& entities = dynamicPart.dynamicEntities;
                std::vector<std::shared_ptr<omniscia::core::Entity>> outEntities;
                
                for(std::shared_ptr<omniscia::core::Entity>& ptr : entities)
                    if(predicate(ptr))
                        outEntities.push_back(ptr);

                return outEntities;
            }

            template<class Predicate>
            std::vector<std::shared_ptr<omniscia::core::Entity>> find_static_entities_with_predicate(const Predicate& predicate) {
                auto& entities = staticPart.staticEntities;
                std::vector<std::shared_ptr<omniscia::core::Entity>> outEntities;

                for(std::shared_ptr<omniscia::core::Entity>& ptr : entities)
                    if(predicate(ptr))
                        outEntities.push_back(ptr);

                return outEntities;
            }

            template<class _T>
            inline std::vector<std::shared_ptr<omniscia::core::Entity>> find_dynamic_entities_by_prototype() {
                return find_dynamic_entities_with_predicate(Predicate_EntityPrototypeEqual<_T>());
            }

            template<class _T>
            inline std::vector<std::shared_ptr<omniscia::core::Entity>> find_static_entities_by_prototype() {
                return find_static_entities_with_predicate(Predicate_EntityPrototypeEqual<_T>());
            }

            void delete_dynamic_entity_by_uuid(const UUID& uuid) {
                auto& entities = dynamicPart.dynamicEntities; 

                for(auto i = entities.begin(); i != entities.end();) {
                    Entity* entity = (*i).get();

                    if(entity->get_uuid() == uuid) {
                        entities.erase(i);
                        time_sync();
                        return;
                    } else
                        ++i;
                } 
            }

            void delete_static_entity_by_uuid(const UUID& uuid) {
                auto& entities = staticPart.staticEntities; 

                for(auto i = entities.begin(); i != entities.end();) {
                    Entity* entity = (*i).get();

                    if(entity->get_uuid() == uuid) {
                        entities.erase(i);
                        time_sync();
                        return;
                    } else
                        ++i;
                } 
            }
    };
}

#endif
