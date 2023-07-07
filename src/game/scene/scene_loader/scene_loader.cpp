#include "scene/scene_loader/scene_loader.h"

void omniscia::core::SceneLoader::load_scene(Scene& level, const std::string& path) {
    std::ifstream file(path, std::ios::out | std::ios::binary);

    if(!file.good())
       throw std::runtime_error("Failed to load file data '" + path + "'");

    nlohmann::json jsonData  = nlohmann::json::parse(file);
    file.close();

    auto& staticEntities = level.staticPart.staticEntities;

    staticEntities.clear();

    using namespace omni::types;
    using namespace omni::reflector;
    using namespace omni::reflector::serialization;

    LevelData levelData = JsonSerializer::json_deserialize<LevelData>(jsonData);

    f32 screenBoxHeight = levelData._screenBoxHeight;

    for(auto& markerGroup : levelData._markerGroups) {
        MarkerGroupData tmpMakerGroup;

        for(MarkerData marker : markerGroup._markers) {
            std::vector<MarkerData>& markers = tmpMakerGroup._markers; 
            markers.push_back(marker);
        }

        level._markerGroups.push_back(tmpMakerGroup);
    }

    for(const TileGroupData& tileGroupData : levelData._tileGroups) {
        std::shared_ptr<Entity> tileGroup = std::make_shared<Entity>();
        RawMeshDataBuilder builder;

        // Tiles
        for(const TileEntity& tileData : tileGroupData._tiles) {
            const std::vector<TileMaterial>& tileMaterials = tileGroupData._tileMaterials;

            omniscia::gfx::sprite::RawMeshData mesh = RawMeshData(
                {
                    Vertex(Vec3f( 1.0f,  1.0f, 0.0f), Vec3f::splat(1.0f), tileMaterials[tileData._materialId]._textureCordsTopRight     ),       // top right
                    Vertex(Vec3f( 1.0f, -1.0f, 0.0f), Vec3f::splat(1.0f), tileMaterials[tileData._materialId]._textureCordsBottomRight  ),       // bottom right
                    Vertex(Vec3f(-1.0f, -1.0f, 0.0f), Vec3f::splat(1.0f), tileMaterials[tileData._materialId]._textureCordsBottomLeft   ),       // bottom left
                    Vertex(Vec3f(-1.0f,  1.0f, 0.0f), Vec3f::splat(1.0f), tileMaterials[tileData._materialId]._textureCordsTopLeft      )        // top left 
                },
                { 0, 1, 3, 1, 2, 3 }
            );

            builder.append(mesh,  tileData._position, tileMaterials[tileData._materialId]._scale);
        }

        tileGroup->add<ECS_Positioned>(0.0f, 0.0f);
        tileGroup->add<ECS_TilemapRenderer>(builder.get(), tileGroupData._textureMaterialAssetId, 9);
        staticEntities.push_back(tileGroup);

        // Collision boxes
        for(const CollisionBoxEntity& collisionBox : tileGroupData._collisionBoxes) {
            const Vec2f& collisionBoxPos = collisionBox._position;
            const Vec2f& rangesX = collisionBox._xRanges;
            const Vec2f& rangesY = collisionBox._yRanges;
            
            std::shared_ptr<Entity> collisionBoxEntity = std::make_shared<Entity>();

            if(collisionBox._isDamaging) {
                collisionBoxEntity->add<ECS_Positioned>(collisionBoxPos.x, collisionBoxPos.y);
                collisionBoxEntity->add<ECS_BoxColliderMesh>(rangesX, rangesY);
                collisionBoxEntity->add<ECS_Deadly>();

                staticEntities.push_back(collisionBoxEntity);
            } else {
                collisionBoxEntity->add<ECS_Positioned>(collisionBoxPos.x, collisionBoxPos.y);
                collisionBoxEntity->add<ECS_BoxColliderMesh>(rangesX, rangesY);
                collisionBoxEntity->add<ECS_AABBCollider>(CollisionMask_Tiles, CollisionMask_None);

                staticEntities.push_back(collisionBoxEntity);
            }
        }
    }
}

omniscia::core::SceneLoader& omniscia::core::SceneLoader::get_instance() {
    static SceneLoader sceneLoader;
    return sceneLoader;
}