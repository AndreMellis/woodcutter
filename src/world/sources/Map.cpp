#include "Map.h"
#include <cstdio>

Map *Map::pInstance = nullptr;

Map *Map::getInstance()
{
    if(!pInstance)
    {
        pInstance = new Map();
    }
    return pInstance;
}

void Map::genMap()
{
    for(int row = 0; row < GameSettings::tileHeightCount; row++ )
    {
        for( int col = 0; col < GameSettings::tileWidthCount; col++ )
        {
            int randomTileType = rand() % asset_AssetCount;
            int tileX = col * GameSettings::tileWidth;
            int tileY = row * GameSettings::tileHeight;

            switch(randomTileType)
            {
                case 0:
                    map[row][col] = Tile( tileX, tileY, TileType::Grass );
                    map[row][col].setCollidable(0);
                    break;
                case 1:
                    map[row][col] = Tile( tileX, tileY, TileType::Water );
                    map[row][col].setCollidable(1);
                    break;
            }
        }
    }
}

void Map::render(SDL_Renderer *renderer, SDL_Texture *pTextureArray[])
{
    for(int row = 0; row < GameSettings::tileHeightCount; row++ )
    {
        for( int col = 0; col < GameSettings::tileWidthCount; col++ )
        {
            switch( map[row][col].getType() )
            {
                case TileType::Grass:
                    SDL_RenderTexture( renderer, pTextureArray[asset_Grass], NULL, map[row][col].getCords() ); // note asset name for array coming from Assets.h
                    break;

                case TileType::Water:
                    SDL_RenderTexture( renderer, pTextureArray[asset_Water], NULL, map[row][col].getCords() ); // note asset name for array coming from Assets.h
                    break;
            }
        }
    }

    // now we will render the selected tile grey
    if(pSelectedTile != nullptr)
    {
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND); //enable alpha on next thing I draw
        SDL_SetRenderDrawColor(renderer, 0xCC, 0xCC, 0xCC, 0x99); // 60% grey
        SDL_RenderFillRect(renderer, pSelectedTile->getCords() );

        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE); //disable alpha on next thing I draw
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF); // go back to drawing white
    }
}

void Map::handleEvent( SDL_Event &event )
{
    if( event.type == SDL_EVENT_MOUSE_BUTTON_DOWN )
    {
        // get the tile the user clicked
        float mouseX;
        float mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        // update pointer
        int tileX = mouseX / GameSettings::tileWidth;
        int tileY = mouseY / GameSettings::tileHeight;

        pSelectedTile = &map[tileY][tileX];

    }
}

Tile *Map::getNeighorTileFromScreenCords(float x, float y, CardinalCord direction)
{
    // transform screen cords to matrix loc
    int matrixX = x / GameSettings::tileWidth;
    int matrixY = y / GameSettings::tileHeight;

    // now let's handle out of bound excepts
    if( matrixX <= 0 && direction == CardinalCord::WEST)
    {
        return nullptr;
    } else if( matrixX >= (GameSettings::tileWidthCount - 1) && direction == CardinalCord::EAST)
    {
        return nullptr;
    } else if( matrixY <= 0 && direction == CardinalCord::NORTH)
    {
        return nullptr;
    } else if( matrixY >= (GameSettings::tileHeightCount - 1) && direction == CardinalCord::SOUTH)
    {
        return nullptr;
    } else{
        switch (direction)
        {
            case CardinalCord::NORTH:
                //north would be x and y-1
                return &map[matrixY-1][matrixX];
                break;

            case CardinalCord::EAST:
                //east would be x+1 and y
                return &map[matrixY][matrixX+1];
                break;

            case CardinalCord::SOUTH:
                //south would be x and y+1
                return &map[matrixY+1][matrixX];
                break;

            case CardinalCord::WEST:
                //west would be x-1 and y
                return &map[matrixY][matrixX-1];
                break;
                break;
        
            default:
                return nullptr;
                break;
        }
    }

    return nullptr; // just to stop the warning. We should never hit this
}