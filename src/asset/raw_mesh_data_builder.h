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
    class RawMeshDataBuilder {
            RawMeshData _meshData;

            u64 maxIndex;
        public:
            RawMeshDataBuilder();

            RawMeshDataBuilder& append(RawMeshData& meshData);
            RawMeshDataBuilder& append(RawMeshData& meshData, const Vec2f& transform);
            RawMeshDataBuilder& append(RawMeshData& meshData, const Vec2f& transform, const f32& angle);
            RawMeshDataBuilder& append(RawMeshData& meshData, const Vec2f& transform, const Vec2f& scale);
            RawMeshDataBuilder& append(RawMeshData& meshData, const Vec2f& transform, const Vec2f& scale, const f32& angle);
            RawMeshDataBuilder& append(RawMeshData& meshData, std::function<void(Vertex& vertex)> lambda);

            RawMeshDataBuilder& transform(const Vec2f& transform);
            RawMeshDataBuilder& scale(const Vec2f& scale);
            RawMeshDataBuilder& rotate(const f32& angle);
            RawMeshDataBuilder& edit(std::function<void(Vertex& vertex)> lambda);

            RawMeshData& get();
    };
}

#endif