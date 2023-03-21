#include "sprite_mesh.h"

omniscia::gfx::sprite::SpriteMesh::SpriteMesh() {

}

omniscia::gfx::sprite::SpriteMesh::SpriteMesh(RawMeshData rawMeshData) : _vao() {
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

omniscia::gfx::sprite::SpriteMesh::SpriteMesh(RawMeshData rawMeshData, const Vec3f& scale) : _vao()  {
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

void omniscia::gfx::sprite::SpriteMesh::bind() const {
    _vao.bind();
}
