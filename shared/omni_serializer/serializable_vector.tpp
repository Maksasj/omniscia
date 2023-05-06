#ifndef _OMNI_SERIALIZER_SERIALIZABLE_VECTOR_H_
#define _OMNI_SERIALIZER_SERIALIZABLE_VECTOR_H_

#include <vector>

#include "serializable.tpp"

namespace omni::serializer {
    using namespace omni::types;
    
    template<class T>
    class SerializableVector : public Serializable<std::vector<T>> {
        public:
            SerializableVector() : Serializable<std::vector<T>>() {}
            SerializableVector(const std::vector<T>& value) : Serializable<std::vector<T>>(value) {}

            void deserialize(std::istream &stream) override {
                std::vector<T>& _value = this->_value;

                Serializable<u64> vectorLength;
                vectorLength.deserialize(stream);

                _value.clear();
                
                for(int i = 0; i < vectorLength; ++i) {
                    T item;
                    item.deserialize(stream);
                    _value.push_back(item);
                }
            }
            
            void serialize(std::ostream &stream) override {
                std::vector<T>& _value = this->_value;

                Serializable<u64> vectorLength = _value.size();
                vectorLength.serialize(stream);

                for(int i = 0; i < vectorLength; ++i)
                    _value[i].serialize(stream);
            }
    };
}

#endif