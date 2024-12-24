#include "ActionHandler.h"

ActionHandler::ActionHandler()
{
    pGameMap = Map::getInstance();
}

void ActionHandler::init(Inventory *pGameInv)
{
    pGameInventory = pGameInv;
}

void ActionHandler::handleEvent(SDL_Event &event)
{
        if (event.type == SDL_EVENT_KEY_DOWN)
        {
            switch( event.key.key )
            {
                case SDLK_H:
                    harvestTree();
                    break;
            }
        }
}

std::pair<int,int> ActionHandler::getFreeNeighbor(int xInput, int yInput, int searchDistance)
{
    int currentDistance = 1; // starting at one because we would never select 0,0
    
    //we need a spot where objectMap[y][x] is Empty and baseMap[y][x] is Grass
    // we will start with objectMap since that will be hardest

    do
    {
        if (yInput - currentDistance < 0)
        { // don't go out of bounds on the Y
            if(
                xInput - currentDistance > 0
                &&
                pGameMap->getObjectMapTileType( (xInput - currentDistance), (yInput - currentDistance) ) == TileType::Empty
                &&
                pGameMap->getBaseMapTileType( (xInput - currentDistance), (yInput - currentDistance) ) == TileType::Grass
                )
                {
                    return std::make_pair( xInput - currentDistance, yInput - currentDistance );
                } 
            
            if(
                pGameMap->getObjectMapTileType( (xInput), (yInput - currentDistance) ) == TileType::Empty
                &&
                pGameMap->getBaseMapTileType( (xInput), (yInput - currentDistance) ) == TileType::Grass
                )
                {
                    return std::make_pair( xInput, yInput - currentDistance );
                } 

            if(
                xInput + currentDistance < GameSettings::mapWidth
                &&
                pGameMap->getObjectMapTileType( (xInput + currentDistance), (yInput - currentDistance) ) == TileType::Empty
                &&
                pGameMap->getBaseMapTileType( (xInput + currentDistance), (yInput - currentDistance) ) == TileType::Grass
                )
                {
                    return std::make_pair( xInput + currentDistance, yInput - currentDistance );
                } 
        } else if ( yInput + currentDistance >= GameSettings::mapHeight)
        { // don't go out of bounds on the Y
            if(
                xInput + currentDistance < GameSettings::mapWidth
                &&
                pGameMap->getObjectMapTileType( (xInput + currentDistance), (yInput + currentDistance) ) == TileType::Empty
                &&
                pGameMap->getBaseMapTileType( (xInput + currentDistance), (yInput + currentDistance) ) == TileType::Grass
                )
                {
                    return std::make_pair( xInput + currentDistance, yInput + currentDistance );
                } 

            if(
                pGameMap->getObjectMapTileType( xInput, (yInput + currentDistance) ) == TileType::Empty
                &&
                pGameMap->getBaseMapTileType( xInput, (yInput + currentDistance) ) == TileType::Grass
                )
                {
                    return std::make_pair( xInput, yInput + currentDistance );
                } 

            if(
                xInput - currentDistance > 0
                &&
                pGameMap->getObjectMapTileType( (xInput - currentDistance), (yInput + currentDistance) ) == TileType::Empty
                &&
                pGameMap->getBaseMapTileType( (xInput - currentDistance), (yInput + currentDistance) ) == TileType::Grass
                )
                {
                    return std::make_pair( (xInput - currentDistance), yInput + currentDistance );
                } 
        } else
        { // same level as Y
            if(
                xInput + currentDistance < GameSettings::mapWidth
                &&
                pGameMap->getObjectMapTileType( (xInput + currentDistance), yInput ) == TileType::Empty
                &&
                pGameMap->getBaseMapTileType( (xInput + currentDistance), yInput ) == TileType::Grass
                )
                {
                    return std::make_pair( xInput + currentDistance, yInput );
                } 

            if(
                xInput - currentDistance > 0
                &&
                pGameMap->getObjectMapTileType( (xInput - currentDistance), yInput ) == TileType::Empty
                &&
                pGameMap->getBaseMapTileType( (xInput - currentDistance), yInput ) == TileType::Grass
                )
                {
                    return std::make_pair( (xInput - currentDistance), yInput );
                } 
        }
    
        currentDistance++;
    } while (currentDistance < (searchDistance + 1) );

    return std::make_pair(-1, -1); // return -1,-1 if no free neighbor found
}

std::pair<int,int> ActionHandler::getNeighoringRoad(int xInput, int yInput, int searchDistance)
{
    int currentDistance = 1; // starting at one because we would never select 0,0
    
    //we need a spot where objectMap[y][x] is Empty and baseMap[y][x] is Grass
    // we will start with objectMap since that will be hardest

    do
    {
        std::pair<int,int> returnMe = std::make_pair( -1, -1 );

        if (yInput - currentDistance < 0)
        { // don't go out of bounds on the Y
            if(
                xInput - currentDistance > 0
                &&
                pGameMap->getBaseMapTileType( (xInput - currentDistance), (yInput - currentDistance) ) == TileType::Road
                )
                {
                    returnMe = getFreeNeighbor( xInput - currentDistance, yInput - currentDistance, 1);
                    if( returnMe.first >= 0 && returnMe.second >= 0 )
                        return returnMe;
                } 
            
            if(
                pGameMap->getBaseMapTileType( (xInput), (yInput - currentDistance) ) == TileType::Road
                )
                {
                    returnMe = getFreeNeighbor( xInput, yInput - currentDistance, 1);
                    if( returnMe.first >= 0 && returnMe.second >= 0 )
                        return returnMe;
                } 

            if(
                xInput + currentDistance < GameSettings::mapWidth
                &&
                pGameMap->getBaseMapTileType( (xInput + currentDistance), (yInput - currentDistance) ) == TileType::Road
                )
                {
                    returnMe = getFreeNeighbor( xInput + currentDistance, yInput - currentDistance, 1);
                    if( returnMe.first >= 0 && returnMe.second >= 0 )
                        return returnMe;
                } 
        } else if ( yInput + currentDistance >= GameSettings::mapHeight)
        { // don't go out of bounds on the Y
            if(
                xInput + currentDistance < GameSettings::mapWidth
                &&
                pGameMap->getBaseMapTileType( (xInput + currentDistance), (yInput + currentDistance) ) == TileType::Road
                )
                {
                    returnMe = getFreeNeighbor( xInput + currentDistance, yInput + currentDistance, 1);
                    if( returnMe.first >= 0 && returnMe.second >= 0 )
                        return returnMe;
                } 

            if(
                pGameMap->getBaseMapTileType( xInput, (yInput + currentDistance) ) == TileType::Road
                )
                {
                    returnMe = getFreeNeighbor( xInput, yInput + currentDistance, 1);
                    if( returnMe.first >= 0 && returnMe.second >= 0 )
                        return returnMe;
                } 

            if(
                xInput - currentDistance > 0
                &&
                pGameMap->getBaseMapTileType( (xInput - currentDistance), (yInput + currentDistance) ) == TileType::Road
                )
                {
                    returnMe = getFreeNeighbor( xInput - currentDistance, yInput + currentDistance, 1);
                    if( returnMe.first >= 0 && returnMe.second >= 0 )
                        return returnMe;
                } 
        } else
        { // same level as Y
            if(
                xInput + currentDistance < GameSettings::mapWidth
                &&
                pGameMap->getBaseMapTileType( (xInput + currentDistance), yInput ) == TileType::Road
                )
                {
                    returnMe = getFreeNeighbor( xInput + currentDistance, yInput, 1);
                    if( returnMe.first >= 0 && returnMe.second >= 0 )
                        return returnMe;
                } 

            if(
                xInput - currentDistance > 0
                &&
                pGameMap->getBaseMapTileType( (xInput - currentDistance), yInput ) == TileType::Road
                )
                {
                    returnMe = getFreeNeighbor( xInput - currentDistance, yInput, 1);
                    if( returnMe.first >= 0 && returnMe.second >= 0 )
                        return returnMe;
                } 
        }

        currentDistance++;
    } while (currentDistance < (searchDistance + 1) );

    return std::make_pair(-1, -1); // return -1,-1 if no free neighbor found
}

void ActionHandler::harvestTree()
{
    int selectedXTile = pGameMap->getSelectedXIndex();
    int selectedYTile = pGameMap->getSelectedYIndex();


    if( selectedXTile < 0 || selectedYTile < 0 || pGameInventory->idleEmployees < 1 )
    {
        return;
    } 
}