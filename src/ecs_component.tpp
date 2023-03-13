#ifndef _ECS_COMPONENT_H_
#define _ECS_COMPONENT_H_

#include <array>
#include <memory>
#include <iostream>

#include "types.h"

namespace omniscia::core::ecs {
    class ECS_Component {
        protected:
            //static u32 _instance;
            //T* const _parent;
        public:
            virtual ~ECS_Component() = default;

            //ECS_Component() {
            //    std::cout << "Calling default component constructor\n";
            //    pp = 0;
            //}

            //ECS_Component(const ECS_Component& another) {
            //    (*this) = another;
            //    pp = 0;
            //    std::cout << "Calling copy component constructor\n";
            //}

            //ECS_Component(const ECS_Component& another) {
            //    *this = another;
            //}

            //template<typename T>
            //bool is_type_off() {
            //    return dynamic_cast<T*>(this);
            //}

            //std::shared_ptr<ECS_Component> clone() const {
            //    return std::make_shared<ECS_Component>(*this);
            //}
//
            //template<typename T>
            //std::shared_ptr<T> clone() const {
            //    return std::make_shared<T>(*((T)this));
            //}

            //template<typename _I>
            //static u32 get_instance() {
            //    return _I::_instance;
            //}
    };
}

#endif