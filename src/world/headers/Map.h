#ifndef MAP_HEADER_
#define MAP_HEADER_

#include <SDL3/SDL.h>
#include <cstdlib>

#include "Tile.h"
#include "Assets.h"
#include "GameSettings.h"
#include "TextureHandler.h"

class Map
{
private:
    Tile map[GameSettings::tileHeightCount][GameSettings::tileWidthCount];
    Tile *pSelectedTile; // the tile currently clicked on the map to render special

    SDL_Texture *mapTextureArray[asset_AssetCount];

public:
    void genMap(); // generates the 2d array with random tiles
    void loadAssets(SDL_Renderer *renderer); // loads all assets to array

    void render(SDL_Renderer *renderer);
    void handleEvent(SDL_Event &event);
};

#endif