#ifndef TILE_HEADER_
#define TILE_HEADER_

#include <SDL.h>

#include "WindowRendering.h"
#include "WindowSettings.h"
#include "Assets.h"

enum class TileType
{
    Grass,
    Water
};

class Tile
{
private:
    WindowRendering *pWindowRenderer = WindowRendering::getInstance();
    WindowSettings windowSettings;
    Assets assets;

    SDL_Rect screenCords;
    TileType type; // empty tile, player tile, etc.
    bool isSelected;
public:
    Tile(int y, int x, TileType inputType); // the X and Y cords of the tile on screen 
    Tile(); // default constructor for array building

    void render();

    void select();
    void deselect();

    SDL_Rect *getCords(); // returns pointer to screen cords
};

#endif