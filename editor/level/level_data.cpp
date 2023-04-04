#include "level_data.h"

omniscia_editor::level_editor::LevelData::LevelData() {

}

void omniscia_editor::level_editor::LevelData::load_from_file(std::string filePath, LevelEditorProperties& levelEditorProperties) {
    std::ifstream f(filePath, std::ios::out | std::ios::binary);

    if(!f.good()) {
        std::cout << "Could not load level data from '" << filePath << "'"; 
        return;
    }

    tileGroups.clear();

    /* Camera screen box */
    u64 screenBoxWidth = 0;
    u64 screenBoxHeight = 0;
    f.read((char* )&screenBoxWidth, sizeof(u64));
    f.read((char* )&screenBoxHeight, sizeof(u64));

    /* Tile groups */
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

void omniscia_editor::level_editor::LevelData::export_to_file(std::string filePath, LevelEditorProperties& levelEditorProperties) {
    std::ofstream f(filePath, std::ios::out | std::ios::binary);
    if(!f.good()) {
        std::cout << "Could not export level to '" << filePath << "'";
        return;
    }

    /* Camera screen box */
    u64 screenBoxWidth = levelEditorProperties._playerScreenWidth;
    u64 screenBoxHeight = levelEditorProperties._playerScreenHeight;
    f.write((char* )&screenBoxWidth, sizeof(u64));
    f.write((char* )&screenBoxHeight, sizeof(u64));

    /* Tile groups */
    u64 tileGroupCount = tileGroups.size();
    f.write((char* )&tileGroupCount, sizeof(u64));

    for(auto& group : tileGroups) {
        u64 tileCount = group.tiles.size();
        f.write((char* )&tileCount, sizeof(u64));

        for(auto tile : group.tiles) {
            auto cords = tile;
            f.write((char* )&cords, sizeof(Tile));
        }
    }
}
