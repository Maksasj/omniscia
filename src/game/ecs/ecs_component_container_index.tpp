/**
 * @file 
 * ecs_component_container_index.tpp
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _ECS_COMPONENT_CONTAINER_INDEX_H_
#define _ECS_COMPONENT_CONTAINER_INDEX_H_

#include <array>

#include "ecs_component.tpp"
#include "omni_types.tpp"

namespace omniscia::core::ecs {
    using namespace omni::types;
    
    /**
     * @brief ECS_Index - class used for 
     * storing index of the specific
     * component instance insight component 
     * container, works like (relative pointer)
     * 
     * @tparam T type of the component 
    */
    template<typename T> 
    class ECS_Index {
        private:
            /** @brief Index of the component inside entity component container */
            u8 _index;

            /** @brief Boolean that show is last indexing that successful */
            bool _success;
            
        public:
            /** 
             * @brief Default constructor of the 
             * ECS_Index class, assumes that indexing failed  
            */
            ECS_Index() : _index(0) { _success = false; }

            /** 
             * @brief Default constructor of the 
             * ECS_Index class, assumes that indexing was successful
             * 
             * @param index of the component that was indexed
            */
            ECS_Index(u32 index) : _index(index) { _success = true; }

            /** 
             * @brief Default constructor of the ECS_Index class
             * 
             * @param success bolean that shows if indexing was successful
            */
            ECS_Index(bool success) {
                _success = success;
            }

            /** 
             * @brief Default constructor of the 
             * ECS_Index class, assuming indexing 
             * failed
            */
            ECS_Index(void*) {
                _success = false;
            }

            /**
             * @brief Getter, checks if indexing was successful
             * 
             * @return true - indexing was successful
             * @return false - indexing failed
            */
            bool is_success() {
                return _success;
            }

            /**
             * @brief Getter, returns index of the component
             * inside entity component container
             * 
             * @return u32 index of the component
            */
            u32 get() const {
                return _index;
            }    
    };
}

#endif