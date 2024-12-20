#ifndef MAP_HEADER_
#define MAP_HEADER_

#include <SDL3/SDL.h>
#include <cstdlib>

#include "Tile.h"
#include "Assets.h"
#include "GameSettings.h"

class Map
{
private:
    Tile map[GameSettings::tileHeightCount][GameSettings::tileWidthCount];
    Tile *pSelectedTile; // the tile currently clicked on the map to render special

public:
    void genMap(); // generates the 2d array with random tiles
    void render(SDL_Renderer *renderer, SDL_Texture *pTextureArray[]);
    void handleEvent(SDL_Event &event);
};

#endif