#ifndef TEXTUREHANDLER_HEADER_
#define TEXTUREHANDLER_HEADER_

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <string>
#include <iostream>

struct TextureHandler
{
    static SDL_Texture *makeTexture(std::string path, SDL_Renderer *renderer); // takes in a png path and returns a texture
};

#endif