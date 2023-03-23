#ifndef _VAO_H_
#define _VAO_H_

#include <vector>

#include "types.tpp"
#include "vertex.h"
#include "gfx.h"
#include "bo.h"

namespace omniscia::gfx {
    class VAO : BO {
        public:
            VAO();
            ~VAO();

            void link_attribute(u32 index, u32 componentsNumber, u32 type, u32 strideSize, void* offset);

            void bind() const override;
            void unbind() const override;

            void terminate() const override;
    };
}

#endif