#ifndef ACTIONHANDLER_HEADER_
#define ACTIONHANDLER_HEADER_

#include <SDL3/SDL.h>
#include <utility>
#include "Inventory.h"
#include "GameSettings.h"
#include "Map.h"

class ActionHandler
{
private:
    Inventory *pGameInventory;
    Map *pGameMap;

    std::pair<int,int> getFreeNeighbor(int xInput, int yInput, int searchDistance); 
    std::pair<int,int> getNeighoringRoad(int xInput, int yInput, int searchDistance); // returns the index of the road closest to the given cords

    void harvestTree();

public:
    ActionHandler();
    void init(Inventory *pGameInv);
    
    void handleEvent(SDL_Event &event);
};

#endif