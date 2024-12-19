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
            int newY = row * WindowSettings::tileHeight;
            int newX = col * WindowSettings::tileWidth;

            switch(randNum)
            {
                case 1:
                    map[row][col] = Tile(newY, newX, TileType::Grass);
                    break;
                case 2:
                    map[row][col] = Tile(newY, newX, TileType::Water);
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
            map[row][col].render();
        }
    }
}

void Map::selectTile(int mouseX, int mouseY)
{
    int tileX = mouseX / WindowSettings::tileWidth;
    int tileY = mouseY / WindowSettings::tileHeight;

    if(selectedTile != nullptr)
    {
        selectedTile->deselect();
    }

    selectedTile = &map[tileY][tileX];
    selectedTile->select();
}

void Map::handleEvent( SDL_Event &event )
{
    if( event.type == SDL_MOUSEBUTTONDOWN )
    { // we clicked something
        int mouseX;
        int mouseY;
        SDL_GetMouseState( &mouseX, &mouseY);
        printf("moused pressed at X: %d Y: %d \n", mouseX, mouseY);
        selectTile(mouseX,mouseY);
    }
    if( event.type == SDL_KEYDOWN && event.key.repeat == 0)
    {
        switch( event.key.keysym.sym)
        {
            case SDLK_ESCAPE:
                if(selectedTile)
                {
                    selectedTile->deselect();
                    selectedTile = nullptr;
                }
                break;
        }
    }
}