#include "level_data.h"

void omniscia_editor::level_editor::LevelData::load_from_file(std::string filePath, LevelEditorOldProperties& levelEditorProperties) {
    std::ifstream file(filePath, std::ios::out | std::ios::binary);

    if(!file.good()) {
        std::cout << "Could not load level data from '" << filePath << "'"; 
        return;
    }
    
    nlohmann::json jsonData  = nlohmann::json::parse(file);
    file.close();

    _tileGroups.clear();

    using namespace omni::reflector;
    using namespace omni::reflector::serialization;
    using namespace omni::types;
    
    omniscia::core::LevelData levelData = json_deserialize<omniscia::core::LevelData>(jsonData);
     
    using namespace omniscia::core;

    _tileGroups = levelData._tileGroups;
    _markerGroups = levelData._markerGroups;

    for(TileGroupData& tileGroup : _tileGroups) {
        for(TileData& tile : tileGroup._tiles) {
            TileData& data = tile; 

            if(levelEditorProperties._exportOpenglCoordinateFlip)
                data._position.y *= -1.0f;
        }
    
        for(CollisionBoxData& collisionBox : tileGroup._collisionBoxes) {
            CollisionBoxData& data = collisionBox;

            if(levelEditorProperties._exportOpenglCoordinateFlip) {
                data._position.y *= -1.0f;
                std::swap(data._yRanges.x, data._yRanges.y);
            }
        }
    }

    for(MarkerGroupData& markerGroup : _markerGroups) {
        for(MarkerData& marker : markerGroup._markers) {
            Vec2f& position = marker._position; 

            if(levelEditorProperties._exportOpenglCoordinateFlip)
                position.y *= -1.0f;
        }
    }
}

void omniscia_editor::level_editor::LevelData::export_to_file(std::string filePath, LevelEditorOldProperties& levelEditorProperties) {
    std::ofstream file(filePath, std::ios::out | std::ios::binary);
    if(!file.good()) {
        std::cout << "Could not export level to '" << filePath << "'";
        return;
    }

    omniscia::core::LevelData levelData;

    levelData._screenBoxWidth = levelEditorProperties._playerScreenWidth;
    levelData._screenBoxHeight = levelEditorProperties._playerScreenHeight;

    levelData._tileGroups = _tileGroups;
    for(TileGroupData& tileGroup : levelData._tileGroups) {
        for(TileData& tileData : tileGroup._tiles) {
            TileData& tile = tileData;
            
            if(levelEditorProperties._exportOpenglCoordinateFlip)
                tile._position.y *= -1.0f;
        }

        for(CollisionBoxData& collisionBoxData : tileGroup._collisionBoxes) {
            CollisionBoxData& collisionBox = collisionBoxData;
            
            if(levelEditorProperties._exportOpenglCoordinateFlip) {
                collisionBox._position.y *= -1.0f;
                std::swap(collisionBox._yRanges.x, collisionBox._yRanges.y);
            }
        }
    }

    levelData._markerGroups = _markerGroups;
    for(MarkerGroupData& markerGroup : levelData._markerGroups) {
        for(MarkerData& marker : markerGroup._markers) {
            Vec2f& position = marker._position;
            
            if(levelEditorProperties._exportOpenglCoordinateFlip)
                position.y *= -1.0f;
        }
    }

    auto json = json_serialize(levelData);
    const auto representation = json.dump(4);
    file << representation;

    file.close();
}
