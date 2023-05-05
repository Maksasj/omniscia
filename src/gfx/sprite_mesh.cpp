#include "sprite_mesh.h"

omniscia::gfx::sprite::SpriteMesh::SpriteMesh() {

}

omniscia::gfx::sprite::SpriteMesh::SpriteMesh(RawMeshData rawMeshData) : _vao() {
    std::vector<Vertex>& _vertices = rawMeshData.get_vertices();
    std::vector<u32>& _indices = rawMeshData.get_indices();

    _verticesSize = _vertices.size();
    _indicesSize = _indices.size();

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
    std::vector<Vertex>& _vertices = rawMeshData.get_vertices();
    std::vector<u32>& _indices = rawMeshData.get_indices();

    _verticesSize = _vertices.size();
    _indicesSize = _indices.size();
    
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

omni::types::u32 omniscia::gfx::sprite::SpriteMesh::get_indices_count() const {
    return _indicesSize;
}

omni::types::u64 omniscia::gfx::sprite::SpriteMesh::byte_size() const {
    return sizeof(SpriteMesh);
}
