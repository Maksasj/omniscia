#ifndef _RAW_MESH_DATA_H_
#define _RAW_MESH_DATA_H_

#include <glad/glad.h>

#include <vector>
#include <algorithm>

#include "vertex.h"

#include "vao.h"
#include "vbo.h"
#include "ebo.h"

#include "types.h"

namespace omniscia::renderer::sprite {
    class RawMeshData {
        std::vector<Vertex> _vertices;
        std::vector<u32> _indices;

        public:
            RawMeshData(const std::vector<Vertex>& vertices, const std::vector<u32>& indices);

            std::vector<Vertex>& get_vetices();

            std::vector<u32>& get_indices();

            static RawMeshData combine(const RawMeshData& first, const RawMeshData& second);
    };
}

#endif