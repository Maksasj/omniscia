# Level file format
*Last time updated 2023-04-08*

## General file structure
```c++
// Primary used only in editor
float screenBoxWidth;
float screenBoxHeight;

unsigned long tileGroupCount;
TileGroup tileGroups[tileGroupCount];
```

Further described memory layout / structure of some in game structures.

### TileGroup structure
```c++
// Primary used only in editor
char tileGroupName[256];
float associatedColor[4];

unsigned long tileCount;
Tile tile[tileCount];

unsigned long collsionBoxesCount;
CollisionBox collisionBoxes[collsionBoxesCount];
```

### Tile structure
```c++
float x;
float y;

float width;
float height;

float textureCordsTopRight[2];
float textureCordsBottomRight[2];
float textureCordsBottomLeft[2];
float textureCordsTopLeft[2];
```

### CollisionBox structure
```c++
// Primary used only in editor
char collisionBoxName[256];
float associatedColor[4];

float x;
float y;

// See ecs_box_collider_mesh.h file, for more info about collision ranges
float rangesX[2];
float rangesY[2];
```