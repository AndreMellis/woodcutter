#include "Builder.h"

Builder::Builder()
{
    mode = BuildMode::NONE;
    pGameMap = Map::getInstance();

    bLoadIsTriggered = 0;
    bSaveIsTriggered = 0;
    uiIsShowing = 0;

    createRects();
}

void Builder::loadAssets(SDL_Renderer *renderer)
{
    builderTextureArray[ROAD_ICON] = TextureHandler::makeTexture("assets/terrain/dirt.png", renderer);
    builderTextureArray[LOAD_ICON] = TextureHandler::makeTexture("assets/icons/load.png", renderer);
    builderTextureArray[SAVE_ICON] = TextureHandler::makeTexture("assets/icons/save.png", renderer);
}

void Builder::renderUI(SDL_Renderer *renderer)
{
    if(uiIsShowing)
    {
        SDL_SetRenderDrawColor(renderer, 217, 217, 217, 1); // solid gray
        SDL_RenderFillRect( renderer, &arrUIRects[UI_BACKGROUND_RECT] ); // draw the solid grey background

        // now I will draw all the lines
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1); // solid black
        int fLineDist = GameSettings::tileWidth;
        for(int lines = fLineDist; lines < GameSettings::windowWidth; lines += fLineDist  )
        {
            SDL_RenderLine( renderer, lines, 0, lines, fBuildUIHeight );
        }
        SDL_RenderLine( renderer, 0, fBuildUIHeight, GameSettings::windowWidth, fBuildUIHeight ); // draw a line along the bottom

        SDL_RenderTexture( renderer, builderTextureArray[ROAD_ICON], NULL, &arrUIRects[ROAD_ICON_RECT] );
        SDL_RenderTexture( renderer, builderTextureArray[LOAD_ICON], NULL, &arrUIRects[UI_LOAD_RECT] );
        SDL_RenderTexture( renderer, builderTextureArray[SAVE_ICON], NULL, &arrUIRects[UI_SAVE_RECT] );
    }
}

void Builder::handleEvent(SDL_Event &event)
{
    if (event.type == SDL_EVENT_KEY_DOWN)
    {
        switch( event.key.key )
        {
            case SDLK_B:
                uiIsShowing = 1;
                break;
            case SDLK_ESCAPE:
                mode = BuildMode::NONE;
                uiIsShowing = 0;
                break;
        }
    }
    if( uiIsShowing && event.type == SDL_EVENT_MOUSE_BUTTON_DOWN )
    {
        float mouseX;
        float mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        handleClick(mouseX, mouseY);
    }
}

void Builder::handleClick(float mouseX, float mouseY)
{
    // make a rect of only the pixel I clicked
    SDL_FRect clickedArea = {mouseX, mouseY, 1, 1};
    
    if( SDL_HasRectIntersectionFloat(&clickedArea, &arrUIRects[ROAD_ICON_RECT] ) )
    {
        // I clicked on the road
        mode = BuildMode::ROAD;
        pGameMap->deselectTile();
    } else if( SDL_HasRectIntersectionFloat(&clickedArea, &arrUIRects[UI_SAVE_RECT] ) )
    {
        bSaveIsTriggered = 1;
    } else if( SDL_HasRectIntersectionFloat(&clickedArea, &arrUIRects[UI_LOAD_RECT] ) )
    {
        bLoadIsTriggered = 1;
    }
}

void Builder::buildItem()
{
    if( mode == BuildMode::NONE || pGameMap->getSelectedTile() == nullptr )
    {
        return;
    } else
    {
        int selectedXTile = pGameMap->getSelectedXIndex();
        int selectedYTile = pGameMap->getSelectedYIndex();

        if( mode == BuildMode::ROAD 
            && 
            pGameMap->getObjectMapTileType(selectedXTile, selectedYTile) == TileType::Empty
            &&
            pGameMap->getBaseMapTileType(selectedXTile, selectedYTile) == TileType::Grass)
        { // I can only build roads on grass blocks
            pGameMap->changeBaseMapTileType(selectedXTile, selectedYTile, TileType::Road);
            pGameMap->deselectTile();
        }
    }
}

void Builder::createRects()
{
    arrUIRects[ROAD_ICON_RECT] = { (ROAD_ICON_RECT * GameSettings::tileWidth) + fIconBorderWidth,
                                    fIconBorderWidth,
                                    GameSettings::tileWidth - ( fIconBorderWidth * 2 ),
                                    fBuildUIHeight - ( fIconBorderWidth * 2 )};

    arrUIRects[UI_LOAD_RECT] = { GameSettings::windowWidth - GameSettings::tileWidth - fIconBorderWidth,
                                 fIconBorderWidth,
                                 GameSettings::tileWidth - ( fIconBorderWidth * 2 ),
                                 fBuildUIHeight - ( fIconBorderWidth * 2) };
    
    arrUIRects[UI_SAVE_RECT] = { GameSettings::windowWidth - ( GameSettings::tileWidth * 2 ) - fIconBorderWidth,
                                 fIconBorderWidth,
                                 GameSettings::tileWidth - ( fIconBorderWidth * 2 ),
                                 fBuildUIHeight - ( fIconBorderWidth * 2) };
    
    
    arrUIRects[UI_BACKGROUND_RECT] = {0, 0, GameSettings::windowWidth,fBuildUIHeight };
}