#include "level_data.h"

void omniscia_editor::level_editor::LevelData::load_from_file(std::string filePath, LevelEditorProperties& levelEditorProperties) {
    std::ifstream file(filePath, std::ios::out | std::ios::binary);

    if(!file.good()) {
        std::cout << "Could not load level data from '" << filePath << "'"; 
        return;
    }

    _tileGroups.get().clear();

    using namespace omni::serializer::binary;
    using namespace omni::types;
    
    SerializableLevelData levelData;
    levelData.deserialize(file);
    
    _tileGroups = levelData._tileGroups;
    _markerGroups = levelData._markerGroups;

    for(SerializableTileGroupData& tileGroup : _tileGroups.get()) {
        for(SerializableTileData& tile : tileGroup._tiles.get()) {
            TileData& data = tile.get(); 

            if(levelEditorProperties._exportOpenglCoordinateFlip)
                data._position.y *= -1.0f;
        }
    
        for(SerializableCollisionBoxData& collisionBox : tileGroup._collisionBoxes.get()) {
            CollisionBoxData& data = collisionBox.get();

            if(levelEditorProperties._exportOpenglCoordinateFlip) {
                data._position.y *= -1.0f;
                std::swap(data._yRanges.x, data._yRanges.y);
            }
        }
    }

    for(SerializableMarkerGroupData& markerGroup : _markerGroups.get()) {
        for(SerializableMarkerData& marker : markerGroup._markers.get()) {
            Vec2f& position = marker._position.get(); 

            if(levelEditorProperties._exportOpenglCoordinateFlip)
                position.y *= -1.0f;
        }
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

    SerializableVector<SerializableTileGroupData> tileGroups = _tileGroups;
    for(SerializableTileGroupData& tileGroup : tileGroups.get()) {
        for(SerializableTileData& tileData : tileGroup._tiles.get()) {
            TileData& tile = tileData.get();
            
            if(levelEditorProperties._exportOpenglCoordinateFlip)
                tile._position.y *= -1.0f;
        }

        for(SerializableCollisionBoxData& collisionBoxData : tileGroup._collisionBoxes.get()) {
            CollisionBoxData& collisionBox = collisionBoxData.get();
            
            if(levelEditorProperties._exportOpenglCoordinateFlip) {
                collisionBox._position.y *= -1.0f;
                std::swap(collisionBox._yRanges.x, collisionBox._yRanges.y);
            }
        }
    }

    SerializableVector<SerializableMarkerGroupData> markerGroups = _markerGroups;
    for(SerializableMarkerGroupData& markerGroup : markerGroups.get()) {
        for(SerializableMarkerData& marker : markerGroup._markers.get()) {
            Vec2f& position = marker._position.get();
            
            if(levelEditorProperties._exportOpenglCoordinateFlip)
                position.y *= -1.0f;
        }
    }

    tileGroups.serialize(file);
    markerGroups.serialize(file);
}
