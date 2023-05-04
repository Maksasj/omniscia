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
                const u64 stringLength = 0;
                char* stringLengthPtr = (char*) (void*) &stringLength;

                stream.read(stringLengthPtr, sizeof(u64));

                _value.clear();
                
                for(int i = 0; i < stringLength; ++i) {
                    char character = 0;
                    stream.read(&character, sizeof(char));
                }
            }
            
            void serialize(std::ostream &stream) override {
                const u64 stringLength = _value.size();
                char* stringLengthPtr = (char*) (void*) &stringLength;

                stream.write(stringLengthPtr, sizeof(u64));

                for(int i = 0; i < stringLength; ++i)
                    stream.write(&_value[i], sizeof(char));
            }
    };
}

#endif