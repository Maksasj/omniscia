#ifndef _OMNI_SERIALIZER_SERIALIZABLE_OBJECT_H_
#define _OMNI_SERIALIZER_SERIALIZABLE_OBJECT_H_

#include <ostream>
#include <istream>

#include "types.tpp"

namespace omni::serializer {
    namespace core {
        class Serializable {
            public:
                virtual void deserialize(std::istream &stream) = 0;
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