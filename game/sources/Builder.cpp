#include "Builder.h"
#include <cstdio>

Builder::Builder()
{
    mode = BuildMode::NONE;
    pGameMap = Map::getInstance();

    uiIsShowing = 0;

    iconRects[ROAD_ICON].x = 0;
    iconRects[ROAD_ICON].y = 0;
    iconRects[ROAD_ICON].w = iconSize;
    iconRects[ROAD_ICON].h = iconSize;
}

void Builder::loadAssets(SDL_Renderer *renderer)
{
    builderTextureArray[ROAD_ICON] = TextureHandler::makeTexture("assets/terrain/dirt.png", renderer);
}

void Builder::renderUI(SDL_Renderer *renderer)
{
    if(uiIsShowing)
    {
        SDL_RenderTexture(renderer, builderTextureArray[ROAD_ICON], NULL, &iconRects[ROAD_ICON]);
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
    
    if( SDL_HasRectIntersectionFloat(&clickedArea, &iconRects[ROAD_ICON] ) )
    {
        // I clicked on the road
        mode = BuildMode::ROAD;
        pGameMap->deselectTile();
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
            *pGameMap->getSelectedTile() = TileType::Road;
            pGameMap->deselectTile();
        }
    }
}