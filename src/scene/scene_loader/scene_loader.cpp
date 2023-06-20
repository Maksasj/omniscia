#include "scene_loader.h"

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

    LevelData levelData = json_deserialize<LevelData>(jsonData);

    f32 screenBoxHeight = levelData._screenBoxHeight;

    for(auto& markerGroup : levelData._markerGroups) {
        MarkerGroupData tmpMakerGroup;

        for(MarkerData marker : markerGroup._markers) {
            Vec2f& pos = marker._position;

            pos = pos / (screenBoxHeight / 2.0);
            pos *= 1.6f;

            std::vector<MarkerData>& markers = tmpMakerGroup._markers; 
            markers.push_back(marker);
        }

        level._markerGroups.push_back(tmpMakerGroup);
    }

    for(TileGroupData& tileGroupData : levelData._tileGroups) {
        std::shared_ptr<Entity> tileGroup = std::make_shared<Entity>();
        RawMeshDataBuilder builder;

        // Tiles
        for(TileData& tileData : tileGroupData._tiles) {
            TileData tile = tileData;

            Vec2f tilePos = tile._position;
            Vec2f tileSize = tile._scale;

            tilePos.x += tileSize.x / 2.0f;
            tilePos.y -= tileSize.y / 2.0f;

            Vec2f newTileSize = tileSize / screenBoxHeight;
            Vec2f newTilePos = tilePos / (screenBoxHeight / 2.0);

            omniscia::gfx::sprite::RawMeshData mesh = RawMeshData(
                {
                    Vertex({ 1.0f,  1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, Vec2f{tile._textureCordsTopRight     }),       // top right
                    Vertex({ 1.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, Vec2f{tile._textureCordsBottomRight  }),     // bottom right
                    Vertex({-1.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, Vec2f{tile._textureCordsBottomLeft   }),       // bottom left
                    Vertex({-1.0f,  1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, Vec2f{tile._textureCordsTopLeft      })          // top left 
                },
                { 0, 1, 3, 1, 2, 3 }
            );

            builder.append(mesh, newTilePos, newTileSize);
        }

        tileGroup->add<ECS_Positioned>(0.0f, 0.0f);
        tileGroup->add<ECS_Scaled>(1.6f, 1.6f);
        tileGroup->add<ECS_TilemapRenderer>(builder.get(), "beach_tiles", 9);
        staticEntities.push_back(tileGroup);

        // Collision boxes
        for(CollisionBoxData& collisionBox : tileGroupData._collisionBoxes) {
            Vec2f collisionBoxPos = collisionBox._position;
            Vec2f rangesX = collisionBox._xRanges;
            Vec2f rangesY = collisionBox._yRanges;
            
            std::shared_ptr<Entity> collisionBoxEntity = std::make_shared<Entity>();

            rangesX /= (screenBoxHeight / 2.0);
            rangesY /= (screenBoxHeight / 2.0);

            collisionBoxPos.x = collisionBoxPos.x / (screenBoxHeight / 2.0);
            collisionBoxPos.y = collisionBoxPos.y / (screenBoxHeight / 2.0);

            if(collisionBox._isDamaging) {
                collisionBoxEntity->add<ECS_Positioned>(collisionBoxPos.x * 1.6f, collisionBoxPos.y * 1.6f);
                collisionBoxEntity->add<ECS_Scaled>(1.6f, 1.6f);
                collisionBoxEntity->add<ECS_BoxColliderMesh>(rangesX, rangesY);
                collisionBoxEntity->add<ECS_Deadly>();

                staticEntities.push_back(collisionBoxEntity);
            } else {
                collisionBoxEntity->add<ECS_Positioned>(collisionBoxPos.x * 1.6f, collisionBoxPos.y * 1.6f);
                collisionBoxEntity->add<ECS_Scaled>(1.6f, 1.6f);
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