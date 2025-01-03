#include "Map.h"

Map *Map::pInstance = 0;

Map *Map::getInstance()
{
    if (!pInstance)
    {
        pInstance = new Map();
    }
    return pInstance;
}

Map::Map()
{
    pSelectedTile = nullptr;
    selectedXIndex = -1;
    selectedYIndex = -1;

    // start camera on far left middle
    cameraX = GameSettings::windowTileWidthCount / 2; // start to the far left
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
            if(row < 3 || row > (GameSettings::mapHeight - 3) || col < 3 || col > (GameSettings::mapWidth - 3) )
            { // all water perim
                baseMap[row][col] = TileType::Water;
                objectMap[row][col] = TileType::Empty;
            } else if(row < 8 || row > (GameSettings::mapHeight - 8) || col < 8 || col > (GameSettings::mapWidth - 8))
            { // fade to grass
                int randNum = 1 + (rand() % 4); // number 1-4
                if(randNum <=3)
                {
                    baseMap[row][col] = TileType::Water;
                    objectMap[row][col] = TileType::Empty;
                } else
                {
                    baseMap[row][col] = TileType::Grass;
                    objectMap[row][col] = TileType::Empty;
                }
            } else if(row < 25 || row > (GameSettings::mapHeight - 25) || col < 25 || col > (GameSettings::mapWidth - 25))
            { // fade in trees
                int randNum = 1 + (rand() % 20); // number 1-4
                if(randNum <=1)
                {
                    baseMap[row][col] = TileType::Grass;
                    objectMap[row][col] = TileType::Tree;
                } else
                {
                    baseMap[row][col] = TileType::Grass;
                    objectMap[row][col] = TileType::Empty;
                }
            } else
            { // we are inland
                int randNum = 1 + (rand() % 20); // number 1-5
                if(randNum <= 8)
                {
                    baseMap[row][col] = TileType::Grass;
                    objectMap[row][col] = TileType::Tree;
                } else
                {
                    baseMap[row][col] = TileType::Grass;
                    objectMap[row][col] = TileType::Empty;
                }
            }
        }
    }

    // now that the map is random, lets add our shop
    int shopsXCord = GameSettings::millXLocation;
    int shopsYCord = GameSettings::millYLocation;

    for( int row = (shopsYCord - 5); row < shopsYCord; row++ )
    {
        for( int col = 0; col < shopsXCord; col++ )
       {
            // I will switch all grass to concrete for the shop
            if( baseMap[row][col] == TileType::Grass)
            {
                baseMap[row][col] = TileType::Concrete;
                objectMap[row][col] = TileType::Empty;
            }
        }
    }

    objectMap[shopsYCord][8] = TileType::Mill;

}

void Map::render(SDL_Renderer *renderer)
{
    int endingRow = cameraY + ( GameSettings::windowTileHeightCount / 2 );
    if(endingRow >= GameSettings::mapHeight)
        endingRow = GameSettings::mapHeight - 1;

    int endingCol = cameraX + ( GameSettings::windowTileWidthCount / 2);
    if(endingCol >= GameSettings::mapWidth)
        endingCol = GameSettings::mapWidth - 1;

    SDL_FRect dstRect;
    dstRect.x = 0;
    dstRect.y = 0;
    dstRect.w = GameSettings::tileWidth;
    dstRect.h = GameSettings::tileHeight;

    float renderingX = 0;
    float renderingY = 0;

    // lets for loop through baseMap first
    for(int row = screenY; row < endingRow; row++ )
    {
        dstRect.y = renderingY * GameSettings::tileHeight;
        renderingX = 0;

        for( int col = screenX; col < endingCol; col++ )
        {
            dstRect.x = renderingX * GameSettings::tileWidth;

            switch( baseMap[row][col] )
            {
                case TileType::Grass:
                    SDL_RenderTexture( renderer, mapTextureArray[asset_Grass], NULL, &dstRect ); // note asset name for array coming from Assets.h
                    break;

                case TileType::Road:
                    SDL_RenderTexture( renderer, mapTextureArray[asset_Dirt], NULL, &dstRect );
                    break;
                
                case TileType::Water:
                    SDL_RenderTexture( renderer, mapTextureArray[asset_Water], NULL, &dstRect ); // note asset name for array coming from Assets.h
                    break;
                
                case TileType::Concrete:
                    SDL_RenderTexture( renderer, mapTextureArray[asset_Concrete], NULL, &dstRect );
                    break;
            }

            if( pSelectedTile == &baseMap[row][col] )  // does the pointer to the selcted tile match the mem addr of this tile
            { // we just printer the selected item
                SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND); //enable alpha on next thing I draw
                SDL_SetRenderDrawColor(renderer, 0xCC, 0xCC, 0xCC, 0x99); // 60% grey
                SDL_RenderFillRect(renderer, &dstRect );

                SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE); //disable alpha on next thing I draw
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF); // go back to drawing white

            }

            renderingX = renderingX + 1.00;
        }

        renderingY = renderingY + 1.00;
    }

    renderingX = 0;
    renderingY = 0;

    // lets for loop through objectMap next
    for(int row = screenY; row < endingRow; row++ )
    {
        dstRect.y = renderingY * GameSettings::tileHeight;
        renderingX = 0;

        for( int col = screenX; col < endingCol; col++ )
        {
            dstRect.x = renderingX * GameSettings::tileWidth;
            SDL_FRect treeRect = { dstRect.x, (dstRect.y - GameSettings::tileHeight), GameSettings::tileWidth, GameSettings::tileHeight*2 }; // specifically for rendering trees

            switch(objectMap[row][col])
            {
                case TileType::Tree:
                    SDL_RenderTexture( renderer, mapTextureArray[asset_Tree], NULL, &treeRect);
                    break;

                case TileType::Stump:
                    SDL_RenderTexture( renderer, mapTextureArray[asset_Stump], NULL, &dstRect ); // note asset name for array coming from Assets.h
                    break;

                case TileType::Mill:
                    // render a grass block first
                    SDL_RenderTexture( renderer, mapTextureArray[asset_Grass], NULL, &dstRect ); // note asset name for array coming from Assets.h

                    // render workshop on top of concrete
                    dstRect.y = (renderingY - 5) * GameSettings::tileHeight;
                    dstRect.h = GameSettings::tileHeight * 5;
                    dstRect.w = GameSettings::tileWidth * 5;
                    SDL_RenderTexture( renderer, mapTextureArray[asset_Mill], NULL, &dstRect );

                    //reset destRect back
                    dstRect.h = GameSettings::tileHeight;
                    dstRect.w = GameSettings::tileWidth;
                    dstRect.y = renderingY * GameSettings::tileHeight;
                    break;
                
                case TileType::UnclaimedLumber:
                    SDL_RenderTexture( renderer, mapTextureArray[asset_UnclaimedLumber], NULL, &dstRect ); // note asset name for array coming from Assets.h
                    break;
                
                case TileType::Worker:
                    SDL_RenderTexture( renderer, mapTextureArray[asset_Worker], NULL, &dstRect ); // note asset name for array coming from Assets.h
                    break;
            }

            renderingX = renderingX + 1.00;
        }

        renderingY = renderingY + 1.00;
    }
}

void Map::handleMouseEvent( SDL_Event &event, bool uiIsTriggered )
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

        if(uiIsTriggered == 0 || tileY > screenY)
        { // you cannot click the top row of tiles while the UI is opened
            pSelectedTile = &baseMap[tileY][tileX];
            selectedXIndex = tileX;
            selectedYIndex = tileY;
        }
    }
}

void Map::handleKeyboardEvent( SDL_Event &event )
{
    if (event.type == SDL_EVENT_KEY_DOWN)
    {
        switch( event.key.key )
        {
            case SDLK_W:
                if(screenY > 0)
                { // we can't go negative
                    cameraY--;
                    screenY--;
                }
                break;

            case SDLK_S:
                if(screenY < (GameSettings::mapHeight) )
                {
                    cameraY++;
                    screenY++;
                }
                break;

            case SDLK_D:
                if(screenX < GameSettings::mapWidth)
                {
                    cameraX++;
                    screenX++;
                }
                break;

            case SDLK_A:
                if(screenX > 0)
                {
                    cameraX--;
                    screenX--;
                }
                break;

            case SDLK_R:
                cameraX = GameSettings::windowTileWidthCount / 2; // start to the far left
                cameraY = GameSettings::mapHeight / 2;
                screenX = cameraX - (GameSettings::windowTileWidthCount / 2);
                screenY = cameraY - (GameSettings::windowTileHeightCount / 2);
                break;
                
            case SDLK_ESCAPE:
                deselectTile();
        }
    }
}

void Map::loadAssets(SDL_Renderer *renderer)
{
    mapTextureArray[asset_Grass] = TextureHandler::makeTexture("assets/terrain/grass.png", renderer);
    mapTextureArray[asset_Water] = TextureHandler::makeTexture("assets/terrain/water.png", renderer);
    mapTextureArray[asset_Dirt] = TextureHandler::makeTexture("assets/terrain/dirt.png", renderer);
    mapTextureArray[asset_Concrete] = TextureHandler::makeTexture("assets/terrain/concrete.png", renderer);
    mapTextureArray[asset_Stump] = TextureHandler::makeTexture("assets/fauna/stump.png", renderer);
    mapTextureArray[asset_Tree] = TextureHandler::makeTexture("assets/fauna/tree.png", renderer);
    mapTextureArray[asset_Mill] = TextureHandler::makeTexture("assets/buildings/sawmill.png", renderer);
    mapTextureArray[asset_UnclaimedLumber] = TextureHandler::makeTexture("assets/objects/lumberPile.png", renderer);
    mapTextureArray[asset_Worker] = TextureHandler::makeTexture("assets/characters/worker.png", renderer);
}

void Map::deselectTile()
{
    pSelectedTile = nullptr;
    selectedXIndex = -1;
    selectedYIndex = -1;
}