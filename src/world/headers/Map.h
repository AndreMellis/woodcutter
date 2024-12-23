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
    TileType map[GameSettings::mapHeight][GameSettings::mapWidth];
    TileType *pSelectedTile; // the tile currently clicked on the map to render special
    static Map *pInstance;

    SDL_Texture *mapTextureArray[asset_AssetCount];

    // we want to center camera on middle of map
    int cameraX;
    int cameraY;

    int screenX; // this will be the Xcord of what's on screen
    int screenY; // this will be the Ycord of what's on screen

    Map();
    ~Map();
public:
    static Map *getInstance();

    void genMap(); // generates the 2d array with random tiles
    void loadAssets(SDL_Renderer *renderer); // loads all assets to array

    void render(SDL_Renderer *renderer);
    void handleKeyboardEvent(SDL_Event &event);
    void handleMouseEvent(SDL_Event &event, bool buildUIIsTriggered);

    void deselectTile() { pSelectedTile = nullptr; }
    TileType *getSelectedTile() { return pSelectedTile; }
};

#endif