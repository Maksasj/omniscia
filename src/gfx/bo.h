#ifndef _BO_H_
#define _BO_H_

#include "types.tpp"

namespace omniscia::renderer {
    
    //Buffer object
    class BO {
        protected:
            u32 _ID;
        public:
            virtual void bind() const {};
            virtual void unbind() const {};

            virtual void terminate() const {};

            u32 get_id() const;
            u32* get_id_ref();
    };
}

#endif