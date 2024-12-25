#ifndef ACTIONHANDLER_HEADER_
#define ACTIONHANDLER_HEADER_

#include <SDL3/SDL.h>
#include <utility>
#include <vector>
#include "Inventory.h"
#include "GameSettings.h"
#include "Map.h"
#include "Tile.h"
#include "AStar.h"

class ActionHandler
{
private:
    Inventory *pGameInventory;
    Map *pGameMap;
    AStar aStar;

    const int maxRoadDistFromTree = 4; // how far we will look for roads away from trees

    std::pair<int,int> getFreeNeighbor(int xInput, int yInput, int searchDistance); 
    std::pair<int,int> getEmptyTileNextToRoad(int xInput, int yInput, int searchDistance); // returns the index of the road closest to the given cords

    void harvestTree();

public:
    ActionHandler();
    void init(Inventory *pGameInv);
    
    void handleEvent(SDL_Event &event);
    void step(); // this will handle things we do once a frame
};

#endif