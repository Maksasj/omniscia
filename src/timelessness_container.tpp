#ifndef _TIMELESSNESS_CONTAINER_H_
#define _TIMELESSNESS_CONTAINER_H_

#include "types.tpp"

namespace omniscia::core {
    template<class __T, u64 __size>
    class TimeLessNessContainer {
        private:
            __T _data[__size];
            u64 _size;

            i64 _currentIndex;
        public:
            TimeLessNessContainer() : _size(__size) {
                _currentIndex = 0;
            }

            void push(const __T& value) {
                ++_currentIndex;
                if(_currentIndex >= __size)
                    _currentIndex = 0;
            
                _data[_currentIndex] = value;
            }

            __T& get() {
                return _data[_currentIndex];
            } 

            void pop() {
                --_currentIndex;

                if(_currentIndex < 0)
                    _currentIndex = __size - 1;
            }

            u64 size() {
                return __size;
            }

            i64 get_index() {
                return _currentIndex;
            }
    };
}

#endif