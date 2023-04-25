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

#include "cutscene.h"

namespace omniscia::core {
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

        public:
            friend class SceneLoader;

            /**
             * @brief Method used for cloning dynamic scene part
             * 
             * @return SceneDynamic new dynamic scene part instance
            */
            SceneDynamic clone();

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
                return entities[entities.size() - 1]->get_uuid();
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
                return entities[entities.size() - 1]->get_uuid();
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
                return entities[entities.size() - 1]->get_uuid();
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
                return entities[entities.size() - 1]->get_uuid();
            }

            std::shared_ptr<Entity> get_dynamic_entity_by_uuid(const UUID& uuid) {
                for(auto& e : dynamicPart.dynamicEntities)
                    if(e->get_uuid() == uuid)
                        return e;

                return nullptr;
            }
    
            std::shared_ptr<Entity> get_static_entity_by_uuid(const UUID& uuid) {
                for(auto& e : staticPart.staticEntities)
                    if(e->get_uuid() == uuid)
                        return e;

                return nullptr;
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

            template<class T>
            T* get_dynamic_entity_by_prototype() {
                auto& entities = dynamicPart.dynamicEntities;

                for(auto& sharedPtr : entities) {
                    Entity* ptr = sharedPtr.get();

                    if(dynamic_cast<T*>(ptr))
                        return static_cast<T*>(ptr);
                }

                return nullptr;
            }

            template<class T>
            T* get_static_entity_by_prototype() {
                auto& entities = staticPart.staticEntities;

                for(auto& sharedPtr : entities) {
                    Entity* ptr = sharedPtr.get();

                    if(dynamic_cast<T*>(ptr))
                        return static_cast<T*>(ptr);
                }

                return nullptr;
            }

            template<class T>
            std::vector<T*> get_dynamic_entities_by_prototype() {
                auto& entities = dynamicPart.dynamicEntities;
                std::vector<T*> outEntities;

                for(auto& sharedPtr : entities) {
                    Entity* ptr = sharedPtr.get();

                    if(dynamic_cast<T*>(ptr))
                        outEntities.push_back(static_cast<T*>(ptr));
                }

                return outEntities;
            }

            template<class T>
            std::vector<T*> get_static_entities_by_prototype() {
                auto& entities = staticPart.staticEntities;
                std::vector<T*> outEntities;

                for(auto& sharedPtr : entities) {
                    Entity* ptr = sharedPtr.get();

                    if(dynamic_cast<T*>(ptr))
                        outEntities.push_back(static_cast<T*>(ptr));
                }

                return outEntities;
            }
    };
}

#endif
