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
    TileType baseMap[GameSettings::mapHeight][GameSettings::mapWidth];
    TileType objectMap[GameSettings::mapHeight][GameSettings::mapWidth];
    static Map *pInstance;

    SDL_Texture *mapTextureArray[asset_AssetCount];

    TileType *pSelectedTile; // the tile currently clicked on the map to render special
    int selectedXIndex; // index of the currently selected tile
    int selectedYIndex; // index of the currently selected tile

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

    void deselectTile();
    TileType *getSelectedTile() { return pSelectedTile; }

    TileType getBaseMapTileType(int x, int y) { return baseMap[y][x]; }
    TileType getObjectMapTileType(int x, int y) { return objectMap[y][x]; }
    void changeBaseMapTileType(int x, int y, TileType newType) { baseMap[y][x] = newType; }
    void changeObjectMapTileType(int x, int y, TileType newType) { objectMap[y][x] = newType; }

    int getSelectedXIndex() { return selectedXIndex; }
    int getSelectedYIndex() { return selectedYIndex; }

};

#endif