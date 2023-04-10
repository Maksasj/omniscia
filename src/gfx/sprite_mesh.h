#ifndef _SPRITE_MESH_H_
#define _SPRITE_MESH_H_

#include <vector>

#include "raw_mesh_data.h"
#include "types.tpp"
#include "vertex.h"
#include "vao.h"
#include "vbo.h"
#include "ebo.h"
#include "gfx.h"

namespace omniscia::gfx::sprite {
    using namespace omniscia::core;

    class SpriteMesh {
        private:
            u32 _verticesSize;
            u32 _indicesSize;

            VAO _vao;
        public:
            SpriteMesh();
            SpriteMesh(RawMeshData rawMeshData);
            SpriteMesh(RawMeshData rawMeshData, const Vec3f& scale);

            void bind() const;
            u32 get_indices_count() const;

            u64 byte_size() const {
                return sizeof(SpriteMesh);
            }
    };
}

#endif