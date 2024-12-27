#ifndef BUILDER_HEADER_
#define BUILDER_HEADER_

#include <SDL3/SDL.h>
#include "TextureHandler.h"
#include "GameSettings.h"
#include "Tile.h"
#include "Map.h"

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

    enum UIRects{ ROAD_ICON_RECT, UI_SAVE_RECT, UI_LOAD_RECT, UI_BACKGROUND_RECT, UI_RECT_SIZE };
    enum buildIcons { ROAD_ICON, SAVE_ICON, LOAD_ICON, ICON_COUNT };   

    SDL_FRect arrUIRects[UI_RECT_SIZE];
    SDL_Texture *builderTextureArray[ICON_COUNT];

    const float fIconBorderWidth = 5.00;
    const int iconSize = 20;
    const float fBuildUIHeight = GameSettings::tileHeight;

    void handleClick(float mouseX, float mouseY);
    void createRects(); //creates all the rects in arrUIRects

public:
    Builder();
    void loadAssets(SDL_Renderer *renderer);

    void renderUI(SDL_Renderer *renderer);
    void handleEvent(SDL_Event &event);
    void buildItem(); // if in build mode and tile is selected, build it

    bool uiIsTriggered() { return uiIsShowing; }
    bool bLoadIsTriggered;
    bool bSaveIsTriggered; // this isn't lazy...right?
};

#endif