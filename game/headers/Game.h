#ifndef GAME_HEADERS_
#define GAME_HEADERS_

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

#include "ActionHandler.h"
#include "UserInterface.h"
#include "GameSettings.h"
#include "SaveLoader.h"
#include "Inventory.h"
#include "Builder.h"
#include "DayTime.h"
#include "Assets.h"
#include "Map.h"

class Game
{
private:
    SDL_Renderer *renderer;
    SDL_Window *window;
    TTF_Font *pGameFont;
    Map *pGameMap;
    Builder builder;
    Inventory inventory;
    ActionHandler actionHandler;
    SaveLoader saveLoader;
    DayTime worldClock;
    UserInterface uiHandler;

    bool loadAssets(); // loads all assets into the array

public:
    Game();
    void run(); // run game
    void close();

    bool init();
};

#endif