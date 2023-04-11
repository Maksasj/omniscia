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

            /**
             * @brief Index of the last element
            */
            i64 _currentIndex;

        public:
            /**
             * @brief Default TimeLessNessContainer class constructor
            */
            TimeLessNessContainer() : _size(__size) {
                _currentIndex = 0;
            }

            /**
             * @brief Pushes value to the container
             * 
             * @param value value to be pushed to container
            */
            void push(const __T& value) {
                ++_currentIndex;
                if(_currentIndex >= __size)
                    _currentIndex = 0;
            
                _data[_currentIndex] = value;
            }

            /**
             * @brief Returns reference to the elemnt of the top of container
             * 
             * @return __T& referene to element
             */
            __T& get() {
                return _data[_currentIndex];
            } 

            /**
             * @brief Decrements index of the current item
            */
            void pop() {
                --_currentIndex;

                if(_currentIndex < 0)
                    _currentIndex = __size - 1;
            }

            /**
             * @brief Get max size of the container
             * 
             * @return u64 max size of the container
            */
            u64 size() {
                return __size;
            }

            /**
             * @brief Get the index of current item
             * 
             * @return i64 index of current item
            */
            i64 get_index() {
                return _currentIndex;
            }
    };
}

#endif