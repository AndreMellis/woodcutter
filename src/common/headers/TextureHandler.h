#ifndef TEXTUREHANDLER_HEADER_
#define TEXTUREHANDLER_HEADER_

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>
#include <string>
#include <iostream>

struct TextureHandler
{
    static SDL_Texture *makeTexture(std::string path, SDL_Renderer *renderer); // takes in a png path and returns a texture
    static SDL_Texture *renderTextureFromFont( char inputString[], TTF_Font *gFont, SDL_Renderer *renderer );
};

#endif