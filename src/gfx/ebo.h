#ifndef _EBO_H_
#define _EBO_H_

#include <glad/glad.h>

#include <vector>

#include "bo.h"

namespace omniscia::gfx {
    class EBO : BO {
        public:
            EBO(const std::vector<u32>& indices);

            void bind() const override;
            void unbind() const override;

            void terminate() const override;
    };
}

#endif