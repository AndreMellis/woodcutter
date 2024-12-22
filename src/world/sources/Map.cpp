#include "Map.h"

void Map::genMap()
{
    pSelectedTile = nullptr;

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

void Map::render(SDL_Renderer *renderer)
{
    for(int row = 0; row < GameSettings::tileHeightCount; row++ )
    {
        for( int col = 0; col < GameSettings::tileWidthCount; col++ )
        {
            switch( map[row][col].getType() )
            {
                case TileType::Grass:
                    SDL_RenderTexture( renderer, mapTextureArray[asset_Grass], NULL, map[row][col].getCords() ); // note asset name for array coming from Assets.h
                    break;

                case TileType::Water:
                    SDL_RenderTexture( renderer, mapTextureArray[asset_Water], NULL, map[row][col].getCords() ); // note asset name for array coming from Assets.h
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

void Map::loadAssets(SDL_Renderer *renderer)
{
    mapTextureArray[asset_Grass] = TextureHandler::makeTexture("assets/terrain/grass.png", renderer);
    mapTextureArray[asset_Water] = TextureHandler::makeTexture("assets/terrain/water.png", renderer);
}