#include "Map.h"

Map::Map()
{
    pSelectedTile = nullptr;

    // center camera on map
    cameraX = GameSettings::mapWidth / 2;
    cameraY = GameSettings::mapHeight / 2;
}

void Map::genMap()
{
    for(int row = 0; row < GameSettings::mapHeight; row++ )
    {
        for( int col = 0; col < GameSettings::mapWidth; col++ )
        {
            int randomTileType = rand() % asset_AssetCount;

            switch(randomTileType)
            {
                case 0:
                    map[row][col] = TileType::Grass;
                    break;
                case 1:
                    map[row][col] = TileType::Water;
                    break;
            }
        }
    }
}

void Map::render(SDL_Renderer *renderer)
{
    int startingRow = cameraY - ( GameSettings::windowTileHeightCount / 2 );
    if(startingRow < 0)
        startingRow = 0;

    int endingRow = cameraY + ( GameSettings::windowTileHeightCount / 2 );
    if(endingRow > GameSettings::mapHeight)
        endingRow = GameSettings::mapHeight;

    int startingCol = cameraX - ( GameSettings::windowTileWidthCount / 2);
    if(startingCol < 0)
        startingCol = 0;
    
    int endingCol = cameraX + ( GameSettings::windowTileWidthCount / 2);
    if(endingCol > GameSettings::mapWidth)
        endingCol = GameSettings::mapWidth;

    SDL_FRect dstRect;
    dstRect.x = 0;
    dstRect.y = 0;
    dstRect.w = GameSettings::tileWidth;
    dstRect.h = GameSettings::tileHeight;

    float screenX = 0;
    float screenY = 0;
    
    for(int row = startingRow; row < endingRow; row++ )
    {
        dstRect.y = screenY * GameSettings::tileHeight;
        screenX = 0;

        for( int col = startingCol; col < endingCol; col++ )
        {
            dstRect.x = screenX * GameSettings::tileWidth;

            switch( map[row][col] )
            {
                case TileType::Grass:
                    SDL_RenderTexture( renderer, mapTextureArray[asset_Grass], NULL, &dstRect ); // note asset name for array coming from Assets.h
                    break;

                case TileType::Water:
                    SDL_RenderTexture( renderer, mapTextureArray[asset_Water], NULL, &dstRect ); // note asset name for array coming from Assets.h
                    break;
            }

            screenX = screenX + 1.00;
        }

        screenY = screenY + 1.00;
    }

    // now we will render the selected tile grey
    if(pSelectedTile != nullptr)
    {
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND); //enable alpha on next thing I draw
        SDL_SetRenderDrawColor(renderer, 0xCC, 0xCC, 0xCC, 0x99); // 60% grey
        //SDL_RenderFillRect(renderer, pSelectedTile->getCords() );

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

    } else if (event.type == SDL_EVENT_KEY_DOWN)
    {
        switch( event.key.key )
        {
            case SDLK_W:
                cameraY--;
                break;
            case SDLK_S:
                cameraY++;
                break;
            case SDLK_D:
                cameraX++;
                break;
            case SDLK_A:
                cameraX--;
                break;
        }
        printf("CameraX: %d - CameraY: %d\n", cameraX, cameraY);
    }
}

void Map::loadAssets(SDL_Renderer *renderer)
{
    mapTextureArray[asset_Grass] = TextureHandler::makeTexture("assets/terrain/grass.png", renderer);
    mapTextureArray[asset_Water] = TextureHandler::makeTexture("assets/terrain/water.png", renderer);
}