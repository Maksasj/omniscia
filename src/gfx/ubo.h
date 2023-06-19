/**
 * @file 
 * vbo.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _UBO_H_
#define _UBO_H_

#include <vector>

#include "omni_types.tpp"
#include "vertex.h"
#include "gfx.h"
#include "bo.h"
#include "instancing_data.h"

namespace omniscia::gfx {
    using namespace omni::types;

    class UBO : public BO {
        private:

        public:
            UBO();

            void bind() const override;
            
            void unbind() const override;

            void terminate() const override;

            InstancingData* open() const {
                return (InstancingData*)glMapBufferRange(GL_UNIFORM_BUFFER, 0, UNIFORM_INSTANCING_DATA_SIZE * sizeof(InstancingData), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
            }

            void close() const {
                glUnmapBuffer(GL_UNIFORM_BUFFER);
                unbind();
            }
    };
}

#endif