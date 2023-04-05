#ifndef _OMNISCIA_EDITOR_LEVEL_EDITOR_PROPERTIES_H_
#define _OMNISCIA_EDITOR_LEVEL_EDITOR_PROPERTIES_H_

#include "types.h"
#include "gfx.h"

namespace omniscia_editor::level_editor {
    struct LevelEditorProperties {
        bool _renderGrid;
        bool _renderAxis;

        bool _gridSnap;
        f32 _gridSize;
        f32 _gridSizeMin;
        f32 _gridSizeMax;

        f32 _interactionRadius;
        f32 _interactionRadiusMin;
        f32 _interactionRadiusMax;

        ImVec2 _scroll;
        i32 _brushMode;
        bool _brushModeTilePerfect;
        bool _brushContinuous;
        i32 _brushSize;
        i32 _brushSizeMax;
        i32 _brushSizeMin;
        i32 _brushType;

        f32 _brushTileWidth;
        f32 _brushTileHeight;
        f32 _brushTileWidthMax;
        f32 _brushTileWidthMin;
        f32 _brushTileHeightMax;
        f32 _brushTileHeightMin;
        f32 _brushTileDefaultWidth;
        f32 _brushTileDefaultHeight;

        i32 _selectedTileGroup;
        i32 _selectedCollisionBox;

        f32 _minZoom;
        f32 _maxZoom;
        f32 _zoomSpeed;
        f32 _zoom;

        bool _renderPlayerCameraBox;
        f32 _playerScreenWidth;
        f32 _playerScreenHeight;

        bool _exportAllTileGroups;
        bool _exportOpenglCoordinateFlip;

        LevelEditorProperties& get_properties();
    };
}

#endif
