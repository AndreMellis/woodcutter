#ifndef TILE_HEADER_
#define TILE_HEADER_

#include <SDL3/SDL.h>
#include "GameSettings.h"

enum class TileType
{
    Grass,
    Water,
    Road,
    Tree,
    Stump,
    Concrete,
    Mill,
    UnclaimedLumber,
    Empty
};

#endif