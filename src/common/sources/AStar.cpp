#include "AStar.h"
#include <cstdio>

AStar::AStar()
{
    pGameMap = Map::getInstance();
}

void AStar::updateNodeMap()
{

    for( int row = 0; row < GameSettings::mapHeight; row++)
    {
        for( int col = 0; col < GameSettings::mapWidth; col++)
        {
            arrNodeMap[row][col].x = col;
            arrNodeMap[row][col].y = row;
            arrNodeMap[row][col].parentNode = nullptr;
            arrNodeMap[row][col].bHasBeenVisited = 0;
            arrNodeMap[row][col].fLocalGoal = std::numeric_limits<int>::max();
            arrNodeMap[row][col].fGlobalGoal = std::numeric_limits<int>::max();
            arrNodeMap[row][col].vecNeighbors.clear();

            switch( pGameMap->getObjectMapTileType(col, row) )
            {
                case TileType::Empty:
                case TileType::Worker:
                    arrNodeMap[row][col].bIsObstacle = 0;
                    break;

                default:
                    arrNodeMap[row][col].bIsObstacle = 1;
                    break;
            }

            // Add all the neighbors
            if(row > 0)
            { // we have a north neighbor
                if( (col - 1) > 0 ) // we have a left neighbor
                    arrNodeMap[row][col].vecNeighbors.push_back( &arrNodeMap[row - 1][col - 1] );

                if( (col + 1) < (GameSettings::mapWidth - 1) ) // we have a right neighbor
                    arrNodeMap[row][col].vecNeighbors.push_back( &arrNodeMap[row - 1][col + 1] );

                // we have an immediate north neighbor
                arrNodeMap[row][col].vecNeighbors.push_back( &arrNodeMap[row - 1][col] );
            }

            if(row < GameSettings::mapHeight - 1)
            { // we have a southern neighbor
                if( (col - 1) > 0 ) // we have a left neighbor
                    arrNodeMap[row][col].vecNeighbors.push_back( &arrNodeMap[row + 1][col - 1] );

                if( (col + 1) < (GameSettings::mapWidth - 1) ) // we have a right neighbor
                    arrNodeMap[row][col].vecNeighbors.push_back( &arrNodeMap[row + 1][col + 1] );

                // we have an immediate north neighbor
                arrNodeMap[row][col].vecNeighbors.push_back( &arrNodeMap[row + 1][col] );
            }

            if( (col - 1) > 0 ) // we have an immediate left neighbor
                arrNodeMap[row][col].vecNeighbors.push_back( &arrNodeMap[row][col - 1] );

            if( (col + 1) < (GameSettings::mapWidth - 1) ) // we have an immediate right neighbor
                arrNodeMap[row][col].vecNeighbors.push_back( &arrNodeMap[row][col + 1] );
        }
    }
    printf("Node[100][8] has %d neighbors\n", arrNodeMap[100][8].vecNeighbors.size());
}

void AStar::unvisitAllNodes()
{
    for( int row = 0; row < GameSettings::mapHeight; row++ )
    {
        for( int col = 0; col < GameSettings::mapWidth; col++ )
        {
            arrNodeMap[row][col].parentNode = nullptr;
            arrNodeMap[row][col].bHasBeenVisited = 0;
            arrNodeMap[row][col].fLocalGoal = std::numeric_limits<int>::max();
            arrNodeMap[row][col].fGlobalGoal = std::numeric_limits<int>::max();
        }
    }
}

std::vector< std::pair<int, int> > AStar::findPath( int startX, int startY, int endX, int endY)
{
    unvisitAllNodes(); // slightly inefficient at the start, but we will always unvisit all nodes before finding a new path

    // the nodes we start and end with
    Node *startNode = &arrNodeMap[startY][startX];
    printf("startNode is arrNodeMap[%d][%d]\n", startY, startX);
    printf("startNode has %d neighbors\n", startNode->vecNeighbors.size());
    Node *endNode = &arrNodeMap[endY][endX];

    /*
     * we will return a vector of pairs that are the X, Y cords of the map
     * so pathToTake[0].first would be the first tile's x
     *    pathToTake[0].second would be the first tile's y
    */
    std::vector< std::pair<int, int> > pathToTake;

    auto distance = [](Node* a, Node* b)
    { // a lambda function for pythagorean theorem???
        return std::sqrtf((a->x - b->x)*(a->x - b->x) + (a->y - b->y)*(a->y - b->y));
    };

    auto heuristic = [distance](Node* a, Node* b)
    { // the "as the crow flies" distance between a and b
        return std::distance(a, b);
    };

    // set the start node up
    Node *nodeCurrent = startNode;
    nodeCurrent->fLocalGoal = 0.0f; // there is no distance from the start because you are the start
    nodeCurrent->fGlobalGoal = heuristic(startNode, endNode); // the straight-line distance from start to end

    // Add start node to the not tested list to ensure it's tested
    std::list<Node*> listNotTestedNodes;
    listNotTestedNodes.push_back(startNode);

    // main meat and potatoes
    while( !listNotTestedNodes.empty() && nodeCurrent != endNode )
    { // while there are nodes to test
        listNotTestedNodes.sort([](const Node* lhs, const Node* rhs){return lhs->fGlobalGoal < rhs->fGlobalGoal; }); //ion know anymore.. a smallest to largest sort

            while( !listNotTestedNodes.empty() && listNotTestedNodes.front()->bHasBeenVisited) // we already visited the first item in the list
                listNotTestedNodes.pop_front();

            if(listNotTestedNodes.empty()) // if we emptied the whole list from step above. break out func
                break; 
            
            nodeCurrent = listNotTestedNodes.front();
            nodeCurrent->bHasBeenVisited = 1;

            for( auto nodeNeighbor : nodeCurrent->vecNeighbors )
            { // if the node hasn't been visited and is not an obstacle. add it to the test list
                if( !nodeNeighbor->bHasBeenVisited && nodeNeighbor->bIsObstacle == 0)
                    listNotTestedNodes.push_back(nodeNeighbor);

                float fPossiblyLowerGoal = nodeCurrent->fLocalGoal + distance(nodeCurrent, nodeNeighbor);
                if( fPossiblyLowerGoal < nodeNeighbor->fLocalGoal )
                {
                    nodeNeighbor->parentNode = nodeCurrent;
                    nodeNeighbor->fLocalGoal = fPossiblyLowerGoal;

                    // the best path to the nieghbor has changed, so update the neighbor score
                    nodeNeighbor->fGlobalGoal = nodeNeighbor->fLocalGoal + heuristic(nodeNeighbor, endNode);
                }
            }
    }

    Node *p = endNode;
    while(p->parentNode != nullptr)
    {
        int parentX = p->parentNode->x;
        int parentY = p->parentNode->y;

        pathToTake.push_back( std::make_pair( parentX, parentY ) );

        p = p->parentNode;
    }

    return pathToTake;
}