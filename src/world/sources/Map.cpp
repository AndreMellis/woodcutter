#include "Map.h"

Map::Map()
{
    pSelectedTile = nullptr;

    // center camera on map
    cameraX = GameSettings::mapWidth / 2;
    cameraY = GameSettings::mapHeight / 2;

    screenX = cameraX - (GameSettings::windowTileWidthCount / 2);
    screenY = cameraY - (GameSettings::windowTileHeightCount / 2);
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
    int endingRow = cameraY + ( GameSettings::windowTileHeightCount / 2 );
    if(endingRow > GameSettings::mapHeight)
        endingRow = GameSettings::mapHeight;

    int endingCol = cameraX + ( GameSettings::windowTileWidthCount / 2);
    if(endingCol > GameSettings::mapWidth)
        endingCol = GameSettings::mapWidth;

    SDL_FRect dstRect;
    dstRect.x = 0;
    dstRect.y = 0;
    dstRect.w = GameSettings::tileWidth;
    dstRect.h = GameSettings::tileHeight;

    float renderingX = 0;
    float renderingY = 0;
    
    for(int row = screenY; row < endingRow; row++ )
    {
        dstRect.y = renderingY * GameSettings::tileHeight;
        renderingX = 0;

        for( int col = screenX; col < endingCol; col++ )
        {
            dstRect.x = renderingX * GameSettings::tileWidth;

            switch( map[row][col] )
            {
                case TileType::Grass:
                    SDL_RenderTexture( renderer, mapTextureArray[asset_Grass], NULL, &dstRect ); // note asset name for array coming from Assets.h
                    break;

                case TileType::Water:
                    SDL_RenderTexture( renderer, mapTextureArray[asset_Water], NULL, &dstRect ); // note asset name for array coming from Assets.h
                    break;
            }

            renderingX = renderingX + 1.00;
        }

        renderingY = renderingY + 1.00;
    }

    // now we will render the selected tile grey
    if(pSelectedTile != nullptr)
    {
        *pSelectedTile = TileType::Empty;
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
        int tileX = screenX + (mouseX / GameSettings::tileWidth);
        int tileY = screenY + (mouseY / GameSettings::tileHeight);

        pSelectedTile = &map[tileY][tileX];

    } else if (event.type == SDL_EVENT_KEY_DOWN)
    {
        switch( event.key.key )
        {
            case SDLK_W:
                cameraY--;
                screenY--;
                break;
            case SDLK_S:
                cameraY++;
                screenY++;
                break;
            case SDLK_D:
                cameraX++;
                screenX++;
                break;
            case SDLK_A:
                cameraX--;
                screenX--;
                break;
        }
    }
}

void Map::loadAssets(SDL_Renderer *renderer)
{
    mapTextureArray[asset_Grass] = TextureHandler::makeTexture("assets/terrain/grass.png", renderer);
    mapTextureArray[asset_Water] = TextureHandler::makeTexture("assets/terrain/water.png", renderer);
}