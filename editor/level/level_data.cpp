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
    f.read((char* )&levelEditorProperties._playerScreenWidth, sizeof(f32));
    f.read((char* )&levelEditorProperties._playerScreenHeight, sizeof(f32));

    /* Tile groups */
    u64 tileGroupCount = 0;
    f.read((char *)&tileGroupCount, sizeof(u64));
    
    for(u64 i = 0; i < tileGroupCount; ++i) {
        /* Tile group*/
        TileGroup group("Group");

        /* Tile group name*/
        f.read((char*)&group._name, 256);

        /* Associated Color */
        ImVec4& associatedColor = group._associatedColor;
        f.read((char* )&associatedColor, sizeof(ImVec4));

        u64 tileCount = 0;
        f.read((char *)&tileCount, sizeof(u64));

        /* Tiles */
        for(u64 j = 0; j < tileCount; ++j) {
            Tile tile;
            f.read((char *)&tile, sizeof(Tile));

            if(levelEditorProperties._exportOpenglCoordinateFlip)
                tile.y *= -1.0f;

            group.tiles.push_back(tile);
        }

        u64 collsionBoxesCount = 0;
        f.read((char* )&collsionBoxesCount, sizeof(u64));
        for(u64 j = 0; j < collsionBoxesCount; ++j) {
            CollisionBox collisionBox;

            f.read((char *)&collisionBox, sizeof(CollisionBox));
            
            if(levelEditorProperties._exportOpenglCoordinateFlip) {
                collisionBox._y *= -1.0f;
                std::swap(collisionBox._rangesY.x, collisionBox._rangesY.y);
            }

            group._collisionBoxes.push_back(collisionBox);
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
    f32 screenBoxWidth = levelEditorProperties._playerScreenWidth;
    f32 screenBoxHeight = levelEditorProperties._playerScreenHeight;
    f.write((char* )&screenBoxWidth, sizeof(f32));
    f.write((char* )&screenBoxHeight, sizeof(f32));

    /* Tile groups count */
    u64 tileGroupCount = tileGroups.size();
    f.write((char* )&tileGroupCount, sizeof(u64));

    /* Tile groups */
    for(auto& group : tileGroups) {
        /* Tile group */
        /* Name */
        f.write(group._name, 256);

        /* Associated Color */
        ImVec4 associatedColor = group._associatedColor;
        f.write((char* )&associatedColor, sizeof(ImVec4));
        
        /* Tiles */
        u64 tileCount = group.tiles.size();
        f.write((char* )&tileCount, sizeof(u64));

        for(auto tile : group.tiles) {
            auto cords = tile;

            if(levelEditorProperties._exportOpenglCoordinateFlip)
                cords.y *= -1;

            f.write((char* )&cords, sizeof(Tile));
        }

        /* Collision boxes */
        u64 collsionBoxesCount = group._collisionBoxes.size();
        f.write((char* )&collsionBoxesCount, sizeof(u64));

        for(auto collsionBox : group._collisionBoxes) {
            auto box = collsionBox;


            if(levelEditorProperties._exportOpenglCoordinateFlip) {
                box._y *= -1;
                std::swap(box._rangesY.x, box._rangesY.y);
            }

            f.write(box._name, 256);
            f.write((char*)&box._associatedColor, sizeof(ImVec4));
            f.write((char*)&box._x, sizeof(f32));
            f.write((char*)&box._y, sizeof(f32));
            f.write((char*)&box._rangesX, sizeof(omniscia::core::Vec2f));
            f.write((char*)&box._rangesY, sizeof(omniscia::core::Vec2f));
        }
    }
}
