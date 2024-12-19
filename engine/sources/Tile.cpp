#include "Tile.h"
#include <cstdio>

Tile::Tile(int y, int x, TileType inputType)
{
    screenCords.y = y;
    screenCords.x = x;
    screenCords.h = windowSettings.tileHeight;
    screenCords.w = windowSettings.tileWidth;

    type = inputType;
    isSelected = 0;
}

Tile::Tile()
{
}

void Tile::select()
{
    isSelected = 1;
}

void Tile::deselect()
{
    isSelected = 0;
}

void Tile::render()
{
    switch(type)
    {
        case TileType::Grass:
            pWindowRenderer->drawImg( assets.grassImage, &screenCords);
            break;
        case TileType::Water:
            pWindowRenderer->drawImg( assets.waterImage, &screenCords );
            break;
    }

    if(isSelected)
    { // if it's selected, fade it
        pWindowRenderer->fadeRect(&screenCords);
    }
}

SDL_Rect *Tile::getCords()
{
    return &screenCords;
}