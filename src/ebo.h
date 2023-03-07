#ifndef _EBO_H_
#define _EBO_H_

#include <glad/glad.h>

#include <vector>

#include "bo.h"

namespace omniscia::renderer {
    class EBO : BO {
        public:
            EBO(const std::vector<u32>& indices);

            void bind() override;
            void unbind() override;

            void terminate() override;
    };
}

#endif