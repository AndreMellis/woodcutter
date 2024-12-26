#ifndef ACTIONS_HEADER_
#define ACTIONS_HEADER_

#include <utility>
#include <stack>
#include "GameSettings.h"
#include "Map.h"
#include "Tile.h"
#include "AStar.h"

class Actions
{
private:
    Map *pGameMap;

    const int maxRoadDistFromTree = 4; // how far we will look for roads away from trees

    std::pair<int,int> getFreeNeighbor(int xInput, int yInput, int searchDistance); 
    std::pair<int,int> getEmptyTileNextToRoad(int xInput, int yInput, int searchDistance); // returns the index of the road closest to the given cords

public:
    Actions();

    void harvestTree(int inputXLocation, int inputYLocation);
};

#endif