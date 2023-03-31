#ifndef _RAW_MESH_DATA_BUILDER_H_
#define _RAW_MESH_DATA_BUILDER_H_

#include <vector>
#include <iostream>
#include <algorithm>

#include "types.tpp"
#include "raw_mesh_data.h"
#include "build_in_mesh_data.h"

namespace omniscia::gfx::sprite {
    class RawMeshDataBuilder {
            RawMeshData _meshData;

            u64 maxIndex = 0;
        public:
            RawMeshDataBuilder() {
                maxIndex = 0;
            }

            /*
            RawMeshDataBuilder& append(RawMeshData& meshData) {
                auto& vertices = _meshData.get_vetices();
                auto& indecies = _meshData.get_indices();

                u64 maxIndex = 0;

                for(auto& ind : indecies)
                    if(maxIndex < ind) 
                        maxIndex = ind;

                auto& incomingVertices = meshData.get_vetices();
                auto& incomingIndecies = meshData.get_indices();

                for(auto& vert : incomingVertices)
                    vertices.push_back(vert);

                for(auto& ind : incomingIndecies)
                    indecies.push_back(maxIndex + ind);

                return *this;
            }
            */

            RawMeshDataBuilder& append(RawMeshData& meshData, const Vec2f& translate) {
                auto& vertices = _meshData.get_vetices();
                auto& indecies = _meshData.get_indices();

                auto& incomingVertices = meshData.get_vetices();
                auto& incomingIndecies = meshData.get_indices();

                for(auto vert : incomingVertices) {
                    vert.translate(Vec3f{translate.x, translate.y, 0.0f});
                    vertices.push_back(vert);
                }

                u64 tmpMaxIndex = maxIndex;
                for(auto& ind : incomingIndecies) {
                    u64 index = maxIndex + ind;
                    indecies.push_back(index);

                    if(index > tmpMaxIndex)
                        tmpMaxIndex = index;
                }

                if(maxIndex < tmpMaxIndex)
                    maxIndex = tmpMaxIndex + 1;

                return *this;
            }

            RawMeshData& get() {
                return _meshData;
            }
    };
}

#endif