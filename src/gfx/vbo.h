#ifndef _VBO_H_
#define _VBO_H_

#include <vector>

#include "types.tpp"
#include "vertex.h"
#include "gfx.h"
#include "bo.h"

namespace omniscia::gfx {
    class VBO : private BO {
        public:
            VBO(const std::vector<Vertex>& vertices);

            void bind() const override;
            void unbind() const override;

            void terminate() const override;
    };
}

#endif