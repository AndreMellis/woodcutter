#include "TextureHandler.h"

SDL_Texture *TextureHandler::makeTexture(std::string path, SDL_Renderer *renderer)
{
    SDL_Surface *tempSurface = nullptr;
    SDL_Texture *tempTexture = nullptr;

    tempSurface = IMG_Load( path.c_str() );
    if(!tempSurface)
    {
        std::cerr << "Failed to load image " << path << "! SDL_Error: " << SDL_GetError() << "\n";
    } else
    {
        tempTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
        if(!tempTexture)
            std::cerr << "Failed to create texture from " << path << "! SDL_Error: " << SDL_GetError() << "\n";
    }

    SDL_DestroySurface(tempSurface);
    tempSurface = nullptr;

    return tempTexture;
}