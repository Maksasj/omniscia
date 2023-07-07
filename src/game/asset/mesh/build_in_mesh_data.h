/**
 * @file 
 * build_in_mesh_data.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _BUILD_IN_MESH_DATA_H_
#define _BUILD_IN_MESH_DATA_H_

#include "raw_mesh_data.h"
#include "gfx.h"

namespace omniscia::gfx {
    using namespace omni::types;
    using namespace sprite;
    
    /**
     * @brief Class that stores some build in meshes
    */
    struct BuildInMeshData {
        
        /**
         * @brief Build in quad mesh data
        */
        static RawMeshData QUAD_MESH_DATA;
    };
}

#endif