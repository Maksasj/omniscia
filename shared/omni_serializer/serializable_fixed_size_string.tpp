#ifndef _OMNI_SERIALIZER_SERIALIZABLE_FIXED_SIZE_STRING_H_
#define _OMNI_SERIALIZER_SERIALIZABLE_FIXED_SIZE_STRING_H_

#include <string> 

#include "serializable.tpp"

namespace omni::serializer {
    template<unsigned long long __size>
    class SerializableFixedSizeString : public Serializable<std::string> {
        public:
            using u64 = unsigned long long;

            SerializableFixedSizeString() : Serializable<std::string>() {}
            SerializableFixedSizeString(const std::string& value) : Serializable<std::string>(value) {}

            void deserialize(std::istream &stream) override {
                _value.resize(__size);
                _value.clear();
                
                for(int i = 0; i < __size; ++i) {
                    char character = 0;
                    stream.read(&character, sizeof(char));
                }
            }
            
            void serialize(std::ostream &stream) override {
                for(int i = 0; i < __size; ++i)
                    stream.write(&_value[i], sizeof(char));
            }

            friend std::ostream &operator<<(std::ostream &output, const SerializableFixedSizeString<__size>& instance) { 
                output << instance._value;
                return output;            
            }
    };
}

#endif