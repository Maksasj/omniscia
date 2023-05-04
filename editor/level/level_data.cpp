#include "level_data.h"

omniscia_editor::level_editor::LevelData::LevelData() {

}

void omniscia_editor::level_editor::LevelData::load_from_file(std::string filePath, LevelEditorProperties& levelEditorProperties) {
    std::ifstream file(filePath, std::ios::out | std::ios::binary);

    if(!file.good()) {
        std::cout << "Could not load level data from '" << filePath << "'"; 
        return;
    }

    tileGroups.clear();

    using namespace omni::serializer;
    SerializableLevelData levelData;
    levelData.deserialize(file);

    int i = 0;
    for(SerializableTileGroupData& tileGroupData : levelData._tileGroups.get()) {
        TileGroup group((std::string("groupppppssss") + std::to_string(0) + std::string(" ")));
        group._associatedColor = tileGroupData._tileGroupAssociatedColor.get();

        for(SerializableTileData& tileData : tileGroupData._tiles.get()) {
            TileData tile = tileData.get();

            if(levelEditorProperties._exportOpenglCoordinateFlip)
                tile._position.y *= -1.0f;

            group.tiles.push_back(tile);
        }

        for(SerializableCollisionBoxData& collisionBoxData : tileGroupData._collisionBoxes.get()) {
            CollisionBoxData collisionBox = collisionBoxData.get();
            
            if(levelEditorProperties._exportOpenglCoordinateFlip) {
                collisionBox._position.y *= -1.0f;
                std::swap(collisionBox._yRanges.x, collisionBox._yRanges.y);
            }

            group._collisionBoxes.push_back(collisionBox);
        }
        
        tileGroups.push_back(group);
    }
}

void omniscia_editor::level_editor::LevelData::export_to_file(std::string filePath, LevelEditorProperties& levelEditorProperties) {
    std::ofstream file(filePath, std::ios::out | std::ios::binary);
    if(!file.good()) {
        std::cout << "Could not export level to '" << filePath << "'";
        return;
    }

    Serializable<f32> screenBoxWidth = levelEditorProperties._playerScreenWidth;
    Serializable<f32> screenBoxHeight = levelEditorProperties._playerScreenHeight;
    screenBoxWidth.serialize(file);
    screenBoxHeight.serialize(file);

    Serializable<u64> tileGroupCount = tileGroups.size();
    tileGroupCount.serialize(file);
    
    for(TileGroup& tileGroup : tileGroups) {
        SerializableTileGroupData tileGroupData;

        //tileGroupData._name.get() = tileGroup._name;
        tileGroupData._name.get().resize(256, 'a');

        tileGroupData._tileGroupAssociatedColor.get() = tileGroup._associatedColor;

        for(auto& tile : tileGroup.tiles)
            tileGroupData._tiles.get().push_back(tile);

        std::cout << tileGroup.tiles.size() << "\n";

        for(auto& collisionBox : tileGroup._collisionBoxes)
            tileGroupData._collisionBoxes.get().push_back(collisionBox);

        tileGroupData.serialize(file);
    }
}
