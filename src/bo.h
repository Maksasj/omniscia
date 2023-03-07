#ifndef _BO_H_
#define _BO_H_

#include "types.h"

namespace omniscia::renderer {
    
    //Buffer object
    class BO {
        protected:
            u32 _ID;
        public:
            virtual void bind() {};
            virtual void unbind() {};

            virtual void terminate() {};

            u32 get_id() const;
    };
}

#endif