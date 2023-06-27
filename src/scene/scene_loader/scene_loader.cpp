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
            omniscia::gfx::sprite::RawMeshData mesh = RawMeshData(
                {
                    Vertex({ 1.0f,  1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, Vec2f{tileData._textureCordsTopRight     }),       // top right
                    Vertex({ 1.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, Vec2f{tileData._textureCordsBottomRight  }),     // bottom right
                    Vertex({-1.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, Vec2f{tileData._textureCordsBottomLeft   }),       // bottom left
                    Vertex({-1.0f,  1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, Vec2f{tileData._textureCordsTopLeft      })          // top left 
                },
                { 0, 1, 3, 1, 2, 3 }
            );

            builder.append(mesh,  tileData._position, tileData._scale);
        }

        tileGroup->add<ECS_Positioned>(0.0f, 0.0f);
        tileGroup->add<ECS_TilemapRenderer>(builder.get(), "beach_tiles", 9);
        staticEntities.push_back(tileGroup);

        // Collision boxes
        for(CollisionBoxData& collisionBox : tileGroupData._collisionBoxes) {
            Vec2f collisionBoxPos = collisionBox._position;
            Vec2f rangesX = collisionBox._xRanges;
            Vec2f rangesY = collisionBox._yRanges;
            
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