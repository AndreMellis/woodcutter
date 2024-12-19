#ifndef MAP_HEADER_
#define MAP_HEADER_

#include "Tile.h"
#include "WindowSettings.h"

#include <SDL.h>

class Map
{
private:
    Tile map[ WindowSettings::tileHeightCount ][ WindowSettings::tileWidthCount ];
    Tile *selectedTile; // when a mouse is clicked, this points directly to the tile in the arr

    void genMap(); // fill the map with Data

public:
    Map();

    void render();
    void handleEvent( SDL_Event &event );
};

#endif