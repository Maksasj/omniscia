#ifndef _SPRITE_MESH_H_
#define _SPRITE_MESH_H_

#include <glad/glad.h>

#include <vector>

#include "vertex.h"

#include "vao.h"
#include "vbo.h"
#include "ebo.h"

#include "raw_mesh_data.h"

#include "types.h"

namespace omniscia::renderer::sprite {
    using namespace omniscia::core;

    class SpriteMesh {
        private:
            std::vector<Vertex> _vertices;
            std::vector<u32> _indices;

            VAO _vao;
        public:
            SpriteMesh(RawMeshData rawMeshData) : _vao() {
                _vertices = rawMeshData.get_vetices();
                _indices = rawMeshData.get_indices();
                
                _vao.bind();
                    VBO vbo(_vertices);
                    EBO ebo(_indices);

                    vbo.bind();
                        _vao.link_attribute(0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
                        _vao.link_attribute(1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3* sizeof(float)));
                        _vao.link_attribute(2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6* sizeof(float)));
                    vbo.unbind();
                _vao.unbind();

                ebo.unbind();
            }

            SpriteMesh(RawMeshData rawMeshData, const Vec3f& scale) : _vao() {
                _vertices = rawMeshData.get_vetices();
                _indices = rawMeshData.get_indices();
                
                for(auto& vert : _vertices) {
                    vert.scale(scale);
                }

                _vao.bind();
                    VBO vbo(_vertices);
                    EBO ebo(_indices);

                    vbo.bind();
                        _vao.link_attribute(0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
                        _vao.link_attribute(1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3* sizeof(float)));
                        _vao.link_attribute(2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6* sizeof(float)));
                    vbo.unbind();
                _vao.unbind();

                ebo.unbind();
            }

            void bind() {
                _vao.bind();
            }
    };
}

#endif