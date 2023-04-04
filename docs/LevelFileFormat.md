# Level file format
*Last time updated 2023-04-01*

```c++
/* General info */
unsigned long gameVersion; /* Game version target */
unsigned long editorVersion; /* Editor version target */
unsigned long long timeEdited; /* Last edited(Unix time stamp)*/

/* Level name and description */
unsigned long levelNameLength 
char levelName[levelNameLength] /* Level name encoded with ascii*/
unsigned long levelDescriptionLength 
char levelDescription[levelDescriptionLength] /* Level description encoded with ascii*/

/* Level data */
float playerSpawnX;
float playerSpawnY;

unsigned long long tileGroupAmount;
TileGroup group1;
...
...
TileGroup groupI;
...
TileGroup groupN;


{   /* Tile */
    float posX;
    float posY;
    float posZ;

    float sizeWidth;
    float sizeHeight;
}

{   /* Collision box */
    float posX;
    float posY;
    float posZ;

    float rangesXplus;
    float rangesXMinus;
    float rangesYplus;
    float rangesYMinus;
}

{   /* Tile group */
    unsigned long long tileCount;
    Tile tiles[tileCount];

    unsigned long long collisionBoxCount;
    CollisionBox collisionBoxes[collisionBoxCount];
}

```
