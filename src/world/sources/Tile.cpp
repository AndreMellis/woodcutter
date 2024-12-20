#include "Tile.h"

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