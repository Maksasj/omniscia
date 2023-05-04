#ifndef _OMNI_SERIALIZER_SERIALIZABLE_VECTOR_H_
#define _OMNI_SERIALIZER_SERIALIZABLE_VECTOR_H_

#include <vector>

#include "serializable.tpp"

namespace omni::serializer {
    template<class T>
    class SerializableVector : public Serializable<std::vector<T>> {
        public:
            using u64 = unsigned long long;

            SerializableVector() : Serializable<std::vector<T>>() {}
            SerializableVector(const std::vector<T>& value) : Serializable<std::vector<T>>(value) {}

            void deserialize(std::istream &stream) override {
                std::vector<T>& _value = this->_value;

                Serializable<u64> vectorLength;
                vectorLength.deserialize(stream);

                _value.clear();
                _value.resize(vectorLength);
                
                for(int i = 0; i < vectorLength; ++i)
                    _value[i].deserialize(stream);
            }
            
            void serialize(std::ostream &stream) override {
                std::vector<T>& _value = this->_value;

                Serializable<u64> vectorLength;
                vectorLength.serialize(stream);

                for(int i = 0; i < vectorLength; ++i)
                    _value[i].serialize(stream);
            }
    };
}

#endif