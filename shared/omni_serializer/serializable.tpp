#ifndef _OMNI_SERIALIZER_SERIALIZABLE_OBJECT_H_
#define _OMNI_SERIALIZER_SERIALIZABLE_OBJECT_H_

#include <ostream>
#include <istream>

#include "types.tpp"

namespace omni::serializer {
    using namespace omni::types;
    
    namespace core {
        class Serializable {
            public:
                /** @brief create to file */
                virtual void deserialize(std::istream &stream) = 0;

                /** @brief write to file */
                virtual void serialize(std::ostream &stream) = 0;
        };
    }

    template<class T>
    class Serializable : core::Serializable {
        protected:
            T _value;

        public:
            Serializable() : _value() {}
            Serializable(const T& value) : _value(value) {}
            Serializable(const Serializable<T>& self) : _value(self._value) {}

            operator T() { return _value; }
            operator T() const { return _value; }

            T& get() {
                return _value;
            }

            void deserialize(std::istream &stream) override {
                char* ptr = (char*) (void*) &_value;

                stream.read((char* )ptr, sizeof(T));
            }

            void serialize(std::ostream &stream) override {
                char* ptr = (char*) (void*) &_value;

                stream.write(ptr, sizeof(T));
            }
    };
}

#endif