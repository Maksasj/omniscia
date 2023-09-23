#include "asset/mesh/build_in_mesh_data.h"

namespace omniscia::gfx {
    RawMeshData BuildInMeshData::QUAD_MESH_DATA = RawMeshData(
        {
            Vertex({ 1.0f,  1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}),   // top right
            Vertex({ 1.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}),   // bottom right
            Vertex({-1.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}),   // bottom left
            Vertex({-1.0f,  1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f})    // top left 
        },
        { 0, 1, 3, 1, 2, 3 }
    );
}
