#ifndef GAME_HEADERS_
#define GAME_HEADERS_

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

#include "Assets.h"
#include "GameSettings.h"
#include "Map.h"
#include "Builder.h"
#include "Inventory.h"
#include "ActionHandler.h"

class Game
{
private:
    SDL_Renderer *renderer;
    SDL_Window *window;
    Map *pGameMap;
    Builder builder;
    Inventory inventory;
    ActionHandler actionHandler;

    bool loadAssets(); // loads all assets into the array

public:
    Game();
    void run(); // run game
    void close();

    bool init();
};

#endif