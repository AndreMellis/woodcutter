#include "Player.h"

Player::Player()
{
    // for now we will plop player in middle of screen
    directionFacing = CardinalCord::SOUTH;
    screenCords.x = GameSettings::windowWidth / 2;
    screenCords.y = GameSettings::windowHeight / 2;
    screenCords.w = spriteWidth * 1.5;
    screenCords.h = spriteHeight * 1.5;

    inventory.wood=0;
}

bool Player::loadSpriteSheet(SDL_Renderer *renderer)
{
    bool success = 1;

    SDL_Surface *playerSurface = IMG_Load("assets/mobs/playerSheet.png");
    if(!playerSurface)
    {
        std::cerr << "Failed to load assets/mobs/playerSheet to Surface. SDL_Error: " << SDL_GetError() << "\n";
        success = 0;
    } else
    {
        spriteSheetTexture = SDL_CreateTextureFromSurface(renderer, playerSurface);
        if(!spriteSheetTexture)
        {
            std::cerr << "Failed to create texture for assets/mobs/playerSheet to Surface. SDL_Error: " << SDL_GetError() << "\n";
            success = 0;
        }
    }

    SDL_DestroySurface(playerSurface);
    playerSurface = nullptr;

    return success;
}

void Player::render(SDL_Renderer *renderer)
{
    SDL_FRect srcRect;
    srcRect.x = 0;
    srcRect.h = spriteHeight + 4;
    srcRect.w = spriteWidth;

    switch(directionFacing)
    {
        case CardinalCord::NORTH:
            srcRect.y = spriteHeight * (northSpriteSheetRow - 1);
            SDL_RenderTexture( renderer, spriteSheetTexture, &srcRect, &screenCords ); // render the first item in the north row to screen
            break;
        case CardinalCord::EAST:
            srcRect.y = spriteHeight * (eastSpriteSheetRow - 1);
            SDL_RenderTexture( renderer, spriteSheetTexture, &srcRect, &screenCords ); 
            break;
        case CardinalCord::SOUTH:
            srcRect.y = spriteHeight * (southSpriteSheetRow - 1);
            SDL_RenderTexture( renderer, spriteSheetTexture, &srcRect, &screenCords ); 
            break;
        case CardinalCord::WEST:
            srcRect.y = spriteHeight * (westSpriteSheetRow - 1);
            SDL_RenderTexture( renderer, spriteSheetTexture, &srcRect, &screenCords ); 
            break;
    }
}

void Player::handleEvent(SDL_Event &event)
{
    if( event.type == SDL_EVENT_KEY_DOWN )
    {
        switch(event.key.key)
        {
            case SDLK_UP:
            case SDLK_W:
                // to move up decrease y;
                directionFacing = CardinalCord::NORTH;
                screenCords.y = screenCords.y - GameSettings::tileWidth;
                break;
            case SDLK_DOWN:
            case SDLK_S:
                directionFacing = CardinalCord::SOUTH;
                screenCords.y = screenCords.y + GameSettings::tileWidth;
                break;
            case SDLK_RIGHT:
            case SDLK_D:
                directionFacing = CardinalCord::EAST;
                screenCords.x = screenCords.x + GameSettings::tileWidth;
                break;
            case SDLK_LEFT:
            case SDLK_A:
                directionFacing = CardinalCord::WEST;
                screenCords.x = screenCords.x - GameSettings::tileWidth;
                break;
        }
    }
}