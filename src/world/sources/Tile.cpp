#include "Tile.h"
#include <cstdio>

Tile::Tile(float x, float y, TileType inputType)
{
    screenCords.x = x;
    screenCords.y = y;
    screenCords.h = GameSettings::tileHeight;
    screenCords.w = GameSettings::tileWidth;

    type = inputType;
}

Tile::Tile()
{
}

bool Tile::canCollide()
{
    return collidable;
}