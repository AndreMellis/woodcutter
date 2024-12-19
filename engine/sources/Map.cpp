#include "Map.h"
#include <cstdio>

Map::Map()
{
    selectedTile = nullptr;
    genMap();
}

void Map::genMap()
{
    for( int row = 0; row < WindowSettings::tileHeightCount; row++ )
    {
        for( int col = 0; col < WindowSettings::tileWidthCount; col++ )
        {
            // here we need a random tile Type
            int randNum = 1 + (rand() % 2);

            switch(randNum)
            {
                case 1:
                    map[row][col] = Tile( row * WindowSettings::tileHeight, row * WindowSettings::tileWidth, TileType::Grass );
                    printf("row %d col %d was set to grass\n", row, col);
                    break;
                case 2:
                    map[row][col] = Tile( row * WindowSettings::tileHeight, row * WindowSettings::tileWidth, TileType::Water );
                    printf("row %d col %d was set to water\n", row, col);
                    break;
            }
        }
    }
}

void Map::render()
{
    for( int row = 0; row < WindowSettings::tileHeightCount; row++ )
    {
        for( int col = 0; col < WindowSettings::tileWidthCount; col++ )
        {
            printf("rendering row %d col %d\n", row, col);
            map[row][col].render();
        }
    }
}