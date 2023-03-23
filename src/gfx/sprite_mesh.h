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
            std::vector<Vertex> _vertices;
            std::vector<u32> _indices;

            VAO _vao;
        public:
            SpriteMesh();
            SpriteMesh(RawMeshData rawMeshData);
            SpriteMesh(RawMeshData rawMeshData, const Vec3f& scale);

            void bind() const;
    };
}

#endif