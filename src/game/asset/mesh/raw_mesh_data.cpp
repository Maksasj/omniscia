#include "asset/mesh/raw_mesh_data.h"

namespace omniscia::gfx::sprite {
    RawMeshData::RawMeshData() {
        _vertices = std::vector<Vertex>();
        _indices = std::vector<u32>();
    }

    RawMeshData::RawMeshData(const std::vector<Vertex>& vertices, const std::vector<u32>& indices) {
        _vertices = vertices;
        _indices = indices;
    }

    std::vector<Vertex>& RawMeshData::get_vertices() {
        return _vertices;
    }

    std::vector<u32>& RawMeshData::get_indices() {
        return _indices;
    }

    i32 RawMeshData::get_vertices_count() const {
        return _vertices.size();
    }
}
