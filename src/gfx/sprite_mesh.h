/**
 * @file 
 * sprite_mesh.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

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
    using namespace omni::types;

    /**
     * @brief SpriteMesh - class used for stroing
     * vertex array object as well as vertex and
     * indicies count of the stored in this vao mesh
    */
    class SpriteMesh {
        private:
            /** @brief Amount of vertices in the mesh */
            u32 _verticesSize;
            
            /** @brief Amount of indicies in the mesh */
            u32 _indicesSize;
            
            /** @brief VAO associated with this mesh */
            VAO _vao;

        public:
            /** @brief Default SpriteMesh constructor */
            SpriteMesh();

            /**
             * @brief Constructs SpriteMesh using provided raw mesh data
             * 
             * @param rawMeshData raw mesh data that should be used for creating this sprite mesh
            */
            SpriteMesh(RawMeshData rawMeshData);
            
            /**
             * @brief Constructs SpriteMesh using provided raw mesh data
             * 
             * @param rawMeshData raw mesh data that 
             * should be used for creating this sprite mesh
             * @param scale scale of the provided mesh data
             * (rawMeshData will be scaled by this scale) 
            */
            SpriteMesh(RawMeshData rawMeshData, const Vec3f& scale);

            /** @brief Binds sprite mesh (VAO) as an active mesh */
            void bind() const;

            /**
             * @brief Function used to get indices 
             * count of the SpriteMesh instance
             * 
             * @return indices cound 
            */
            u32 get_indices_count() const;

            /**
             * @brief Calculates bytes size of this sprite mesh instance
             * 
             * @return byte size
            */
            u64 byte_size() const;
    };
}

#endif