/**
 * @file 
 * raw_mesh_data_builder.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _RAW_MESH_DATA_BUILDER_H_
#define _RAW_MESH_DATA_BUILDER_H_

#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>

#include "types.tpp"
#include "raw_mesh_data.h"
#include "build_in_mesh_data.h"

namespace omniscia::gfx {
    /**
     * @brief RawMeshDataBuilder - class used for building RawMeshData,
     * mesh merging, combing. Primary used for tile mesh building
     */
    class RawMeshDataBuilder {
        private:
            /** @brief Temporary mesh data */
            RawMeshData _meshData;

            /** @brief Max index of the stored mesh data */
            u64 _maxIndex;
        public:
            /** @brief Defualt constructor of the RawMeshDataBuilder class */
            RawMeshDataBuilder();

            /**
             * @brief Appends provided mesh to the temprory mesh stored in this RawMeshDataBuilder instance
             * 
             * @param meshData mesh to be appended to the temporary mesh
             * @return reference to the current RawMeshDataBuilder instance, used of mehthod chaining
            */
            RawMeshDataBuilder& append(RawMeshData& meshData);
            
            /**
             * @brief Appends provided mesh to the temprory mesh stored in this RawMeshDataBuilder instance, and modifies it vertices
             * 
             * @param meshData mesh to be appended to the temporary mesh
             * @param transform transformation vector for the provided mesh
             * @return reference to the current RawMeshDataBuilder instance, used of mehthod chaining
            */
            RawMeshDataBuilder& append(RawMeshData& meshData, const Vec2f& transform);
            
            /**
             * @brief Appends provided mesh to the temprory mesh stored in this RawMeshDataBuilder instance, and modifies it vertices
             * 
             * @param meshData mesh to be appended to the temporary mesh
             * @param transform transformation vector for the provided mesh
             * @param angle Angle for providedMeshData, append, will rotate provided mesh and only then append to the current temporary
             * @return reference to the current RawMeshDataBuilder instance, used of mehthod chaining
            */
            RawMeshDataBuilder& append(RawMeshData& meshData, const Vec2f& transform, const f32& angle);
            
            /**
             * @brief Appends provided mesh to the temprory mesh stored in this RawMeshDataBuilder instance, and modifies it vertices
             * 
             * @param meshData mesh to be appended to the temporary mesh
             * @param transform transformation vector for the provided mesh
             * @param scale Scales provided mesh, provided mesh will be appended to the temporary mesh only after scaling
             * @return reference to the current RawMeshDataBuilder instance, used of mehthod chaining
            */
            RawMeshDataBuilder& append(RawMeshData& meshData, const Vec2f& transform, const Vec2f& scale);
            
            /**
             * @brief Appends provided mesh to the temprory mesh stored in this RawMeshDataBuilder instance, and modifies it vertices
             * 
             * @param meshData mesh to be appended to the temporary mesh
             * @param transform transformation vector for the provided mesh
             * @param scale Scales provided mesh, provided mesh will be appended to the temporary mesh only after scaling
             * @param angle Angle for providedMeshData, append, will rotate provided mesh and only then append to the current temporary
             * @return reference to the current RawMeshDataBuilder instance, used of mehthod chaining
            */
            RawMeshDataBuilder& append(RawMeshData& meshData, const Vec2f& transform, const Vec2f& scale, const f32& angle);
            
            /**
             * @brief Appends provided mesh to the temprory mesh stored in this RawMeshDataBuilder instance, and modifies it vertices using lamda expression
             * 
             * @param meshData mesh to be appended to the temporary mesh
             * @param lambda expression used for modifining provided mesh vertices
             * @return reference to the current RawMeshDataBuilder instance, used of mehthod chaining
            */
            RawMeshDataBuilder& append(RawMeshData& meshData, std::function<void(Vertex& vertex)> lambda);

            /**
             * @brief Transforms current temporary mesh
             * 
             * @param transform - transformation vector for the current temporary mesh
             * @return reference to the current RawMeshDataBuilder instance, used of mehthod chaining
            */
            RawMeshDataBuilder& transform(const Vec2f& transform);
            
            /**
             * @brief Scale current temporary mesh
             * 
             * @param scale - new size
             * @return reference to the current RawMeshDataBuilder instance, used of mehthod chaining
            */
            RawMeshDataBuilder& scale(const Vec2f& scale);
            
            /**
             * @brief Rotates current temporary mesh
             * 
             * @param angle - the angle by which the mesh will be rotated 
             * @return reference to the current RawMeshDataBuilder instance, used of mehthod chaining
            */
            RawMeshDataBuilder& rotate(const f32& angle);

            /**
             * @brief Applies lamda expression for each vertex of the current temporary mesh
             * 
             * @param lambda expression used for modifining provided mesh vertices
             * @return reference to the current RawMeshDataBuilder instance, used of mehthod chaining
            */
            RawMeshDataBuilder& edit(std::function<void(Vertex& vertex)> lambda);

            /**
             * @brief Returns the temporary mesh
             * 
             * @return reference to the temporary mesh
            */
            RawMeshData& get();
    };
}

#endif