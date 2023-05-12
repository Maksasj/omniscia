#include "raw_mesh_data_builder.h"

omniscia::gfx::RawMeshDataBuilder::RawMeshDataBuilder() {
    _maxIndex = 0;
}

omniscia::gfx::RawMeshDataBuilder& omniscia::gfx::RawMeshDataBuilder::append(RawMeshData& meshData) {
    auto& vertices = _meshData.get_vertices();
    auto& indecies = _meshData.get_indices();

    auto& incomingVertices = meshData.get_vertices();
    auto& incomingIndecies = meshData.get_indices();
    
    vertices.insert(vertices.end(), incomingVertices.begin(), incomingVertices.end());

    u64 tmpMaxIndex = _maxIndex;
    for(auto& ind : incomingIndecies) {
        u64 index = _maxIndex + ind;
        indecies.push_back(index);

        if(index > tmpMaxIndex)
            tmpMaxIndex = index;
    }

    if(_maxIndex < tmpMaxIndex)
        _maxIndex = tmpMaxIndex + 1;

    return *this;
}

omniscia::gfx::RawMeshDataBuilder& omniscia::gfx::RawMeshDataBuilder::append(RawMeshData& meshData, const Vec2f& transform) {
    auto& vertices = _meshData.get_vertices();
    auto& indecies = _meshData.get_indices();

    auto& incomingVertices = meshData.get_vertices();
    auto& incomingIndecies = meshData.get_indices();

    std::transform(incomingVertices.begin(), incomingVertices.end(), incomingVertices.begin(), [&](Vertex vertex) {
        vertex.transform(Vec3f{transform.x, transform.y, 0.0f});
        
        return vertex;
    });

    vertices.insert(vertices.end(), incomingVertices.begin(), incomingVertices.end());

    u64 tmpMaxIndex = _maxIndex;
    for(auto& ind : incomingIndecies) {
        u64 index = _maxIndex + ind;
        indecies.push_back(index);

        if(index > tmpMaxIndex)
            tmpMaxIndex = index;
    }

    if(_maxIndex < tmpMaxIndex)
        _maxIndex = tmpMaxIndex + 1;

    return *this;
}

omniscia::gfx::RawMeshDataBuilder& omniscia::gfx::RawMeshDataBuilder::append(RawMeshData& meshData, const Vec2f& transform, const f32& angle) {
    auto& vertices = _meshData.get_vertices();
    auto& indecies = _meshData.get_indices();

    auto& incomingVertices = meshData.get_vertices();
    auto& incomingIndecies = meshData.get_indices();

    std::transform(incomingVertices.begin(), incomingVertices.end(), incomingVertices.begin(), [&](Vertex vertex) {
        vertex.rotate(angle);
        vertex.transform(Vec3f{transform.x, transform.y, 0.0f});

        return vertex;
    });

    vertices.insert(vertices.end(), incomingVertices.begin(), incomingVertices.end());

    u64 tmpMaxIndex = _maxIndex;
    for(auto& ind : incomingIndecies) {
        u64 index = _maxIndex + ind;
        indecies.push_back(index);

        if(index > tmpMaxIndex)
            tmpMaxIndex = index;
    }

    if(_maxIndex < tmpMaxIndex)
        _maxIndex = tmpMaxIndex + 1;

    return *this;
}

omniscia::gfx::RawMeshDataBuilder& omniscia::gfx::RawMeshDataBuilder::append(RawMeshData& meshData, const Vec2f& transform, const Vec2f& scale) {
    auto& vertices = _meshData.get_vertices();
    auto& indecies = _meshData.get_indices();

    auto& incomingVertices = meshData.get_vertices();
    auto& incomingIndecies = meshData.get_indices();

    std::transform(incomingVertices.begin(), incomingVertices.end(), incomingVertices.begin(), [&](Vertex vertex) {
        vertex.scale(Vec3f{scale.x, scale.y, 1.0});
        vertex.transform(Vec3f{transform.x, transform.y, 0.0f});
        
        return vertex;
    });

    vertices.insert(vertices.end(), incomingVertices.begin(), incomingVertices.end());

    u64 tmpMaxIndex = _maxIndex;
    for(auto& ind : incomingIndecies) {
        u64 index = _maxIndex + ind;
        indecies.push_back(index);

        if(index > tmpMaxIndex)
            tmpMaxIndex = index;
    }

    if(_maxIndex < tmpMaxIndex)
        _maxIndex = tmpMaxIndex + 1;

    return *this;
}

omniscia::gfx::RawMeshDataBuilder& omniscia::gfx::RawMeshDataBuilder::append(RawMeshData& meshData, const Vec2f& transform, const Vec2f& scale, const f32& angle) {
    auto& vertices = _meshData.get_vertices();
    auto& indecies = _meshData.get_indices();

    auto& incomingVertices = meshData.get_vertices();
    auto& incomingIndecies = meshData.get_indices();

    std::transform(incomingVertices.begin(), incomingVertices.end(), incomingVertices.begin(), [&](Vertex vertex) {
        vertex.rotate(angle);
        vertex.scale(Vec3f{scale.x, scale.y, 1.0});
        vertex.transform(Vec3f{transform.x, transform.y, 0.0f});
        
        return vertex;
    });

    vertices.insert(vertices.end(), incomingVertices.begin(), incomingVertices.end());

    u64 tmpMaxIndex = _maxIndex;
    for(auto& ind : incomingIndecies) {
        u64 index = _maxIndex + ind;
        indecies.push_back(index);

        if(index > tmpMaxIndex)
            tmpMaxIndex = index;
    }

    if(_maxIndex < tmpMaxIndex)
        _maxIndex = tmpMaxIndex + 1;

    return *this;
}

omniscia::gfx::RawMeshDataBuilder& omniscia::gfx::RawMeshDataBuilder::append(RawMeshData& meshData, std::function<void(Vertex& vertex)> lambda) {
    auto& vertices = _meshData.get_vertices();
    auto& indecies = _meshData.get_indices();

    auto& incomingVertices = meshData.get_vertices();
    auto& incomingIndecies = meshData.get_indices();

    std::transform(incomingVertices.begin(), incomingVertices.end(), incomingVertices.begin(), [&](Vertex vertex) {
        lambda(vertex);
        
        return vertex;
    });

    vertices.insert(vertices.end(), incomingVertices.begin(), incomingVertices.end());

    u64 tmpMaxIndex = _maxIndex;
    for(auto& ind : incomingIndecies) {
        u64 index = _maxIndex + ind;
        indecies.push_back(index);

        if(index > tmpMaxIndex)
            tmpMaxIndex = index;
    }

    if(_maxIndex < tmpMaxIndex)
        _maxIndex = tmpMaxIndex + 1;

    return *this;
}

omniscia::gfx::RawMeshDataBuilder& omniscia::gfx::RawMeshDataBuilder::transform(const Vec2f& transform) {
    auto& vertices = _meshData.get_vertices();

    std::transform(vertices.begin(), vertices.end(), vertices.begin(), [&](Vertex vertex) {
        vertex.transform(Vec3f{transform.x, transform.y, 0.0f});

        return vertex;
    });

    return *this;
}

omniscia::gfx::RawMeshDataBuilder& omniscia::gfx::RawMeshDataBuilder::scale(const Vec2f& scale) {
    auto& vertices = _meshData.get_vertices();

    std::transform(vertices.begin(), vertices.end(), vertices.begin(), [&](Vertex vertex) {
        vertex.scale(Vec3f{scale.x, scale.y, 0.0f});

        return vertex;
    });

    return *this;
}

omniscia::gfx::RawMeshDataBuilder& omniscia::gfx::RawMeshDataBuilder::rotate(const f32& angle) {
    auto& vertices = _meshData.get_vertices();

    std::transform(vertices.begin(), vertices.end(), vertices.begin(), [&](Vertex vertex) {
        vertex.rotate(angle);

        return vertex;
    });

    return *this;
}

omniscia::gfx::RawMeshDataBuilder& omniscia::gfx::RawMeshDataBuilder::edit(std::function<void(Vertex& vertex)> lambda) {
    auto& vertices = _meshData.get_vertices();

    std::transform(vertices.begin(), vertices.end(), vertices.begin(), [&](Vertex vertex) {
        lambda(vertex);

        return vertex;
    });

    return *this;
}

omniscia::gfx::RawMeshData& omniscia::gfx::RawMeshDataBuilder::get() {
    return _meshData;
}
