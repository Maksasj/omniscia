#include "build_in_mesh_data.h"

namespace omniscia::renderer::sprite {
    const RawMeshData BuildInMeshData::QUAD_MESH_DATA = RawMeshData(
        {
            omniscia::renderer::Vertex({ 1.0f,  1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}),   // top right
            omniscia::renderer::Vertex({ 1.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}),   // bottom right
            omniscia::renderer::Vertex({-1.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}),   // bottom left
            omniscia::renderer::Vertex({-1.0f,  1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f})    // top left 
        },
        { 0, 1, 3, 1, 2, 3 }
    );
}