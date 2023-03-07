#ifndef _VAO_H_
#define _VAO_H_

#include <glad/glad.h>

#include <vector>

#include "bo.h"

#include "vertex.h"
#include "types.h"

namespace omniscia::renderer {
    class VAO : BO {
        public:
            VAO();

            void link_attribute(u32 index, u32 componentsNumber, u32 type, u32 strideSize, void* offset);

            void bind() override;
            void unbind() override;

            void terminate() override;
    };
}

#endif