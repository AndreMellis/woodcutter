#ifndef MAP_HEADER_
#define MAP_HEADER_

#include <SDL3/SDL.h>
#include <cstdlib>

#include "Core.h"
#include "Tile.h"
#include "Assets.h"
#include "GameSettings.h"

class Map
{
private:
    Tile map[GameSettings::tileHeightCount][GameSettings::tileWidthCount];
    Tile *pSelectedTile; // the tile currently clicked on the map to render special
    static Map *pInstance;

    Map(){}
    ~Map(){}

public:
    static Map *getInstance();

    void genMap(); // generates the 2d array with random tiles
    void render(SDL_Renderer *renderer, SDL_Texture *pTextureArray[]);
    void handleEvent(SDL_Event &event);

    Tile *getNeighorTileFromScreenCords(float x, float y, CardinalCord directon); // returns the neighboring tile in a certain direction
};

#endif