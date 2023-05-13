/**
 * @file 
 * timelessness_container.tpp
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _TIMELESSNESS_CONTAINER_H_
#define _TIMELESSNESS_CONTAINER_H_

#include "types.tpp"

namespace omniscia::core {
    using namespace omni::types;
    
    /**
     * @brief Container used for storing, and 
     * automaticlly popping values from back
     * always stores only specifc amount of 
     * the elements
     * 
     * @tparam __T type of the elemnts 
     * @tparam __size size of the cotainer
    */
    template<class __T, u64 __size>
    class TimeLessNessContainer {
        private:
            /**
             * @brief Container data
            */
            __T _data[__size];

            /**
             * @brief Container max size
            */
            u64 _size;
            i64 _actualFrame;

            class iterator;
            friend class iterator;

            iterator _current;


        public:
            /**
             * @brief Default TimeLessNessContainer class constructor
            */
            TimeLessNessContainer() : _size(__size), _current(this, 0), _actualFrame(0) {

            }

            /**
             * @brief Pushes value to the container
             * 
             * @param value value to be pushed to container
            */
            void push(const __T& value) {
                ++_current;
                ++_actualFrame;

                if(_actualFrame > _size)
                    _actualFrame = _size;

                *_current = value;
            }

            /**
             * @brief Returns reference to the elemnt of the top of container
             * 
             * @return __T& referene to element
             */
            __T& get() {
                return *_current;
            } 

            /**
             * @brief Decrements index of the current item
            */
            void pop() {
                --_actualFrame;
                --_current;
            }

            /**
             * @brief Get max size of the container
             * 
             * @return u64 max size of the container
            */
            u64 size() const {
                return __size;
            }

            i64 get_actual_frame() const {
                return _actualFrame;
            }

            /**
             * @brief Get the index of current item
             * 
             * @return i64 index of current item
            */
            i64 get_index() const {
                return _current.get_index();
            }
    };

    template<class __T, u64 __size>
    class TimeLessNessContainer<__T, __size>::iterator {
        private:
            using iterator_category = std::bidirectional_iterator_tag;
            using difference_type   = std::ptrdiff_t;
            using value_type        = __T;
            using pointer           = __T*;
            using reference         = __T&;

            i64 _index;
            TimeLessNessContainer* _container;

        public:
            iterator(TimeLessNessContainer* container, const i32& index) : _container(container), _index(index) {
                if(_index < 0)
                    _index = __size - 1;
            }

            reference operator*() const { 
                return _container->_data[_index];
            }
            
            pointer operator->() { 
                return &_container->_data[_index]; 
            }

            iterator& operator++() { 
                ++_index;
                if(_index >= __size)
                    _index = 0;

                return *this;
            }  
            
            iterator operator++(int) { 
                iterator<__T> tmp = *this;

                ++_index;
                if(_index >= __size)
                    _index = 0;
                
                return tmp;
            }

            iterator& operator--() { 
                --_index;
                if(_index < 0)
                    _index = __size - 1;

                return *this;
            }  
            
            iterator operator--(int) { 
                iterator<__T> tmp = *this;

                --_index;
                if(_index < 0)
                    _index = __size - 1;
                
                return tmp;
            }

            friend bool operator==(const iterator& a, const iterator& b) { 
                return (a._index == b._index) && (a._container == b._container); 
            };
            
            friend bool operator!=(const iterator& a, const iterator& b) { 
                return (a._index != b._index) && (a._container == b._container);
            };     

            i64 get_index() const {
                return _index;
            }
    };
}

#endif