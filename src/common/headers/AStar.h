#ifndef ASTAR_HEADER
#define ASTAR_HEADER

#include "GameSettings.h"
#include "Tile.h"
#include "Map.h"
#include <vector>
#include <utility>
#include <limits>
#include <cmath>
#include <list>
#include <stack>

class AStar
{
private:
    struct Node
    {
        bool bIsObstacle; // is this node an obstacle
        bool bHasBeenVisited; // have we searched this node before
        float fGlobalGoal; // distance to the goal so far
        float fLocalGoal; // distance to the goal if we went another way
        int x; // nodes x cord on map
        int y; // nodes y cord on map

        std::vector<Node*> vecNeighbors; // a vector of pointers to nodes
        Node *parentNode;
    };

    Node arrNodeMap[GameSettings::mapHeight][GameSettings::mapWidth];

    Map *pGameMap;

    void unvisitAllNodes(); // resets all parents, but DOES NOT UPDATE neighbors or map objects

public:
    AStar();
    void updateNodeMap(); // updates the node map, changing all parents to null and updating obsticals from the game

    /*
     * we will return a stack of pairs that are the X, Y cords of the map
    */
    std::stack < std::pair<int, int> > findPath( int startX, int startY, int endX, int endY);
};

#endif