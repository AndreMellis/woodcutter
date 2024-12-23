#ifndef BUILDER_HEADER_
#define BUILDER_HEADER_

#include "Map.h"
#include "Tile.h"
#include "TextureHandler.h"
#include <SDL3/SDL.h>

enum class BuildMode
{
    NONE,
    ROAD
};

class Builder
{
private:
    BuildMode mode;
    Map *pGameMap;
    bool uiIsShowing; // we only want to check for clicks if the ui is up

    const int iconSize = 20;

    enum buildIcons { ROAD_ICON, ICON_COUNT };   
    SDL_Texture *builderTextureArray[ICON_COUNT];
    SDL_FRect iconRects[ICON_COUNT];

    void handleClick(float mouseX, float mouseY);

public:
    Builder();
    void loadAssets(SDL_Renderer *renderer);

    void renderUI(SDL_Renderer *renderer);
    void handleEvent(SDL_Event &event);
    void buildItem(); // if in build mode and tile is selected, build it

    bool uiIsTriggered() { return uiIsShowing; }
};

#endif