#ifndef TILE_HEADER_
#define TILE_HEADER_

#include <SDL3/SDL.h>
#include "GameSettings.h"

enum class TileType
{
    Grass,
    Water
};

class Tile
{
private:
    TileType type;
    SDL_FRect screenCords;
    bool isSelected;

public:
    Tile(float x, float y, TileType inputType);
    Tile(); // default cons for array building

    SDL_FRect *getCords() { return &screenCords; }
    TileType getType() { return type; }
};

#endif