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
            };
            
        public:
            void load_level(Level& level) {
                std::string path = "assets\\levelData.data";

                level.staticPart.staticEntities.clear();

                std::ifstream f(path, std::ios::out | std::ios::binary);

                u64 tileGroupCount = 0;
                f.read((char *)&tileGroupCount, sizeof(u64));
                
                for(u64 i = 0; i < tileGroupCount; ++i) {
                    u64 tileCount = 0;
                    f.read((char *)&tileCount, sizeof(u64));

                    /* TileGroup group("Group"); */
                    Entity tileGroup;
                    RawMeshDataBuilder builder;

                    tileGroup.add<ECS_Positioned>(0.0f, 0.0f);
                    // tileGroup.add<ECS_Scaled>(0.1, 0.1);
                    // builder.append(BuildInMeshData::QUAD_MESH_DATA, {x * 2.0f,y * 2.0f});

                    for(u64 j = 0; j < tileCount; ++j) {
                        TileData tile;
                        f.read((char *)&tile, sizeof(TileData));

                        f32 tileWidth = tile._width / 800.0f;
                        f32 tileHeight = tile._height / 800.0f;

                        builder.append(
                            BuildInMeshData::QUAD_MESH_DATA, 
                            {tile.x * (tile._width / 1280.0f), tile.y * (tile._width / 1280.0f)},
                            {tileWidth, tileHeight}
                            );

                    }

                    tileGroup.add<ECS_TilemapRenderer>(builder.get(), "factorio_girl_texture", 0);
                    level.staticPart.staticEntities.push_back(tileGroup);
                }
            };

            static LevelLoader& get_instance() {
                static LevelLoader levelLoader;
                return levelLoader;
            }
    };
}

#endif
