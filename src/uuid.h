#ifndef _UUID_H_
#define _UUID_H_

#include <string>

#include "omni_types.tpp"
#include "boost_includes.h"

namespace omniscia::core {
    using namespace omni::types;

    class UUID {
        private:
            boost::uuids::uuid _uuid;
        
        public:
            inline std::string to_string() const {
                return boost::lexical_cast<std::string>(_uuid);
            }
            
            static UUID gen_uuid() {
                static boost::uuids::random_generator gen;

                UUID uuid;
                uuid._uuid = gen();

                return uuid;
            }

            inline bool operator==(const UUID& other) const {
                return _uuid == other._uuid;
            }
    };
}

#endif
