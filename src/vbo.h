#ifndef _VBO_H_
#define _VBO_H_

#include <glad/glad.h>

#include <vector>

#include "bo.h"

#include "vertex.h"
#include "types.h"

namespace omniscia::renderer {
    class VBO : private BO {
        public:
            VBO(const std::vector<Vertex>& vertices);

            void bind() override;
            void unbind() override;

            void terminate() override;
    };
}

#endif