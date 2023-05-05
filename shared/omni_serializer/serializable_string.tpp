#ifndef _OMNI_SERIALIZER_SERIALIZABLE_STRING_H_
#define _OMNI_SERIALIZER_SERIALIZABLE_STRING_H_

#include <string> 

#include "serializable.tpp"

namespace omni::serializer {
    class SerializableString : public Serializable<std::string> {
        public:
            using u64 = unsigned long long;

            SerializableString() : Serializable<std::string>() {}
            SerializableString(const std::string& value) : Serializable<std::string>(value) {}

            void deserialize(std::istream &stream) override {
                Serializable<u64> length;
                length.deserialize(stream);
                
                _value.clear();

                for(int i = 0; i < length; ++i) {
                    Serializable<char> character;
                    character.deserialize(stream);
                    _value.push_back(character);
                }
            }
            
            void serialize(std::ostream &stream) override {
                Serializable<u64> length = _value.size();
                length.serialize(stream);

                for(int i = 0; i < length; ++i) {
                    Serializable<char> character = _value[i];
                    character.serialize(stream);
                }
            }
    };
}

#endif