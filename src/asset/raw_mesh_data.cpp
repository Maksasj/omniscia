#include "raw_mesh_data.h"

namespace omniscia::gfx::sprite {
    RawMeshData::RawMeshData() {
        _vertices = std::vector<Vertex>();
        _indices = std::vector<u32>();
    }

    RawMeshData::RawMeshData(const std::vector<Vertex>& vertices, const std::vector<u32>& indices) {
        _vertices = vertices;
        _indices = indices;
    }

    std::vector<Vertex>& RawMeshData::get_vetices() {
        return _vertices;
    }

    std::vector<u32>& RawMeshData::get_indices() {
        return _indices;
    }
}
