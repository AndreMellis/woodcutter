#include "Map.h"
#include <cstdio>

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
                    break;
                case 1:
                    map[row][col] = Tile( tileX, tileY, TileType::Water );
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
}