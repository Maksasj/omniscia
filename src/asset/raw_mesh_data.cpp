#include "raw_mesh_data.h"

namespace omniscia::gfx::sprite {
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

    RawMeshData combine(const RawMeshData& first, const RawMeshData& second) {
        RawMeshData out = first;
        
        //u32 max_index = *std::max_element(out.get_indices().begin(), out.get_indices().end());

        return out;
    }

}
