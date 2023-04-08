#ifndef _LEVEL_LOADER_H_
#define _LEVEL_LOADER_H_

#include "types.tpp"
#include "level.h"

namespace omniscia::core {
    class LevelLoader {
        private:
            struct TileData {
                f32 x;
                f32 y;

                f32 _width;
                f32 _height;

                Vec2f textureCordsTopRight;
                Vec2f textureCordsBottomRight;
                Vec2f textureCordsBottomLeft;
                Vec2f textureCordsTopLeft;
            };
            
        public:
            void load_level(Level& level) {
                std::string path = "assets\\level.bin";
                std::ifstream f(path, std::ios::out | std::ios::binary);

                if(!f.good()) {
                    std::cout << "Could not load '" << path << "' file"; 
                    return;
                }

                auto& staticEntities = level.staticPart.staticEntities;

                staticEntities.clear();

                f32 screenBoxWidth = 0;
                f32 screenBoxHeight = 0;
                f.read((char* )&screenBoxWidth, sizeof(f32));
                f.read((char* )&screenBoxHeight, sizeof(f32));

                u64 tileGroupCount = 0;
                f.read((char *)&tileGroupCount, sizeof(u64));
                
                for(u64 i = 0; i < tileGroupCount; ++i) {
                    /* Name */
                    char name[256];
                    f.read((char *)name, 256);

                    /* Associated color */
                    Vec4f tileGroupAssociatedColor;
                    f.read((char *)&tileGroupAssociatedColor, sizeof(Vec4f));

                    /* TileGroup group("Group"); */
                    Entity tileGroup;
                    RawMeshDataBuilder builder;

                    u64 tileCount = 0;
                    f.read((char *)&tileCount, sizeof(u64));
                    for(u64 j = 0; j < tileCount; ++j) {
                        TileData tile;
                        f.read((char *)&tile, sizeof(TileData));
                        
                        tile.x += tile._width / 2.0f;
                        tile.y -= tile._height / 2.0f;

                        f32 tileWidth = tile._width / screenBoxHeight;
                        f32 tileHeight = tile._height / screenBoxHeight;

                        f32 tilePosX = tile.x / (screenBoxHeight / 2.0);
                        f32 tilePosY = tile.y / (screenBoxHeight / 2.0);

                        /*
                        Vec2f textureCordsTopRight;
                        Vec2f textureCordsBottomRight;
                        Vec2f textureCordsBottomLeft;
                        Vec2f textureCordsTopLeft;
                        */

                        omniscia::gfx::sprite::RawMeshData mesh = RawMeshData(
                            {
                                Vertex({ 1.0f,  1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, tile.textureCordsTopRight),       // top right
                                Vertex({ 1.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, tile.textureCordsBottomRight),     // bottom right
                                Vertex({-1.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, tile.textureCordsBottomLeft),       // bottom left
                                Vertex({-1.0f,  1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, tile.textureCordsTopLeft)          // top left 
                            },
                            { 0, 1, 3, 1, 2, 3 }
                        );

                        builder.append(mesh, {tilePosX, tilePosY}, {tileWidth, tileHeight});
                    }

                    tileGroup.add<ECS_Positioned>(0.0f, 0.0f);
                    tileGroup.add<ECS_Scaled>(1.6f, 1.6f);
                    tileGroup.add<ECS_TilemapRenderer>(builder.get(), "test_tiles", 0);
                    staticEntities.push_back(tileGroup);

                    u64 collisionBoxCount = 0;
                    f.read((char *)&collisionBoxCount, sizeof(u64));
                    for(u64 j = 0; j < collisionBoxCount; ++j) {
                        char array[265];
                        f.read(array, 256);

                        Entity collisionBox;

                        /* Associated color */
                        Vec4f collisionBoxAssociatedColor;
                        f.read((char *)&collisionBoxAssociatedColor, sizeof(Vec4f));

                        f32 x = 0.0f, y = 0.0f;
                        f.read((char *)&x, sizeof(f32));
                        f.read((char *)&y, sizeof(f32));

                        Vec2f rangesX = {0.0f, 0.0f}, rangesY = {0.0f, 0.0f};
                        f.read((char *)&rangesX, sizeof(Vec2f));
                        f.read((char *)&rangesY, sizeof(Vec2f));

                        Vec2f newRangesX = rangesX;
                        Vec2f newRangesY = rangesY;

                        newRangesX /= (screenBoxHeight / 2.0);
                        newRangesY /= (screenBoxHeight / 2.0);

                        x = x / (screenBoxHeight / 2.0);
                        y = y / (screenBoxHeight / 2.0);

                        collisionBox.add<ECS_Scaled>(1.6f, 1.6f);
                        collisionBox.add<ECS_BoxColliderMesh>(newRangesX, newRangesY);
                        collisionBox.add<ECS_AABBCollider>(CollisionMask_Tiles, CollisionMask_None);
                        collisionBox.add<ECS_Positioned>(x * 1.6f, y * 1.6f);

                        staticEntities.push_back(collisionBox);
                    } 
                }
            };

            static LevelLoader& get_instance() {
                static LevelLoader levelLoader;
                return levelLoader;
            }
    };
}

#endif
