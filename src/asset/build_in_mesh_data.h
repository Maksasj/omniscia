#ifndef _BUILD_IN_MESH_DATA_H_
#define _BUILD_IN_MESH_DATA_H_

#include <glad/glad.h>

#include "raw_mesh_data.h"

namespace omniscia::renderer::sprite {
    struct BuildInMeshData {
        static RawMeshData QUAD_MESH_DATA;
    };
}

#endif