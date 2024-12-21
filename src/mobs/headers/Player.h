#ifndef PLAYER_HEADER_
#define PLAYER_HEADER_

#include "GameSettings.h"
#include "Core.h"

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>

class Player
{
private:
    // sprite sheet related items
    const int spriteHeight = 36;
    const int spriteWidth = 24;
    const int frameCount = 8;
    const int northSpriteSheetRow = 5;
    const int eastSpriteSheetRow = 3;
    const int southSpriteSheetRow = 1;
    const int westSpriteSheetRow = 7;

    SDL_Texture *spriteSheetTexture;

    SDL_FRect screenCords;    
    Inventory inventory;

    CardinalCord directionFacing;
    

public:
    Player();
    bool loadSpriteSheet(SDL_Renderer *renderer);

    void render(SDL_Renderer *renderer);
    void handleEvent(SDL_Event &event);
};


#endif