#ifndef _OMNISCIA_EDITOR_LEVEL_DATA_H_
#define _OMNISCIA_EDITOR_LEVEL_DATA_H_

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include "gfx.h"
#include "types.h"

namespace omniscia_editor::level_editor {
    struct Tile {
       f32 x;
       f32 y;

       f32 _width;
       f32 _height;
    };
    

    struct TileGroup {
        std::string _name;
        ImVec4 _associatedColor;
        std::vector<Tile> tiles;

        TileGroup(std::string name) : _name(name) {
            _associatedColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
        }
    };

    struct LevelData {
        std::vector<TileGroup> tileGroups;

        LevelData() {

        }

        void loadToFile(std::string filePath) {
            std::cout << "Loading file from " << filePath << "\n"; 
            tileGroups.clear();

            std::ifstream f(filePath, std::ios::out | std::ios::binary);

            u64 tileGroupCount = 0;
            f.read((char *)&tileGroupCount, sizeof(u64));
            
            for(u64 i = 0; i < tileGroupCount; ++i) {
                u64 tileCount = 0;
                f.read((char *)&tileCount, sizeof(u64));

                TileGroup group("Group");

                for(u64 j = 0; j < tileCount; ++j) {
                    Tile tile;
                    f.read((char *)&tile, sizeof(Tile));

                    group.tiles.push_back(tile);
                }

                tileGroups.push_back(group);
            }
        }

        void export_to_file(std::string filePath) {
            std::cout << "Exporting file too " << filePath << "\n"; 

            std::ofstream f(filePath, std::ios::out | std::ios::binary);

            u64 tileGroupCount = tileGroups.size();
            f.write((char* )&tileGroupCount, sizeof(u64));

            for(auto& group : tileGroups) {
                u64 tileCount = group.tiles.size();
                f.write((char* )&tileCount, sizeof(u64));

                for(auto& tile : group.tiles) {
                    auto cords = tile;
                    f.write((char* )&cords, sizeof(Tile));
                }
            }

            f.close();
        }
    };
}

#endif
