/**
 * @file 
 * raw_mesh_data.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _RAW_MESH_DATA_H_
#define _RAW_MESH_DATA_H_

#include <vector>
#include <iostream>
#include <algorithm>

#include "omni_types.tpp"

#include "gfx/vertex.h"
#include "gfx/vao.h"
#include "gfx/vbo.h"
#include "gfx/ebo.h"
#include "gfx/gfx.h"

namespace omniscia::gfx::sprite {
    using namespace omni::types;

    /**
     * @brief RawMeshData - class used for storing all 
     * Vertices and indices of the mesh
    */
    class RawMeshData {
        /** @brief Vector that stores all Vertices */
        std::vector<Vertex> _vertices;
        
        /** @brief Vector that stores all Indices */
        std::vector<u32> _indices;

        public:
            /** @brief Default constructor of the RawMeshData class */
            RawMeshData();
            
            /**
             * @brief Constucts RawMeshData instances form provided vertex and indices arrays
             * 
             * @param vertices input Vertex array
             * @param indices input Indices array
            */
            RawMeshData(const std::vector<Vertex>& vertices, const std::vector<u32>& indices);

            /**
             * @brief Referecens Vertex array of the RawMeshData instance
             * 
             * @return reference to the Vertex array
            */
            std::vector<Vertex>& get_vertices();

            /**
             * @brief Referecens Indices array of the RawMeshData instance
             * 
             * @return reference to the Index array
            */
            std::vector<u32>& get_indices();

            i32 get_vertices_count() const;
    };
}

#endif