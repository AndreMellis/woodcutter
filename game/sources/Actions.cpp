#include "Actions.h"

Actions::Actions()
{
    pGameMap = Map::getInstance();
}


std::pair<int,int> Actions::getFreeNeighbor(int xInput, int yInput, int searchDistance)
{
    int currentDistance = 1; // starting at one because we would never select 0,0
    
    //we need a spot where objectMap[y][x] is Empty and baseMap[y][x] is Grass
    // we will start with objectMap since that will be hardest

    do
    {
        if (yInput - currentDistance >= 0)
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
                xInput + currentDistance < (GameSettings::mapWidth - 1)
                &&
                pGameMap->getObjectMapTileType( (xInput + currentDistance), (yInput - currentDistance) ) == TileType::Empty
                &&
                pGameMap->getBaseMapTileType( (xInput + currentDistance), (yInput - currentDistance) ) == TileType::Grass
                )
                {
                    return std::make_pair( xInput + currentDistance, yInput - currentDistance );
                } 
        } else if ( yInput + currentDistance < (GameSettings::mapHeight - 1) )
        { // don't go out of bounds on the Y
            if(
                xInput + currentDistance < (GameSettings::mapWidth - 1)
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
                xInput + currentDistance < (GameSettings::mapWidth - 1)
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

std::pair<int,int> Actions::getEmptyTileNextToRoad(int xInput, int yInput, int searchDistance)
{
    int currentDistance = 1; // starting at one because we would never select 0,0
    
    //we need a spot where objectMap[y][x] is Empty and baseMap[y][x] is Grass
    // we will start with objectMap since that will be hardest

    do
    {
        std::pair<int,int> returnMe = std::make_pair( -1, -1 );

        if (yInput - currentDistance > 0)
        { // don't go out of bounds on the Y
            if(
                xInput - currentDistance >= 0
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
                xInput + currentDistance < (GameSettings::mapWidth - 1)
                &&
                pGameMap->getBaseMapTileType( (xInput + currentDistance), (yInput - currentDistance) ) == TileType::Road
                )
                {
                    returnMe = getFreeNeighbor( xInput + currentDistance, yInput - currentDistance, 1);
                    if( returnMe.first >= 0 && returnMe.second >= 0 )
                        return returnMe;
                } 
        } 

        if ( yInput + currentDistance < (GameSettings::mapHeight - 1) )
        { // don't go out of bounds on the Y
            if(
                xInput + currentDistance < (GameSettings::mapWidth - 1)
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
        } 

        // same level as Y
        if(
            xInput + currentDistance < (GameSettings::mapWidth - 1)
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

        currentDistance++;
    } while (currentDistance < (searchDistance + 1) );

    return std::make_pair(-1, -1); // return -1,-1 if no free neighbor found
}

void Actions::harvestTree(int inputXLocation, int inputYLocation)
{
    std::pair<int, int> whereToPlaceLumber = std::make_pair( -1, -1 );

    // first let's look for a road
    whereToPlaceLumber = getEmptyTileNextToRoad(inputXLocation, inputYLocation, maxRoadDistFromTree);

    if( whereToPlaceLumber.first < 0 || whereToPlaceLumber.second < 0 )
    { // a road wasn't found, so we will just drop it on the ground
        whereToPlaceLumber = getFreeNeighbor( inputXLocation, inputYLocation, maxRoadDistFromTree );

        if( whereToPlaceLumber.first < 0 || whereToPlaceLumber.second < 0 )
        { // we just can't harvest the tree at this point
            return;
        }
    }

    //std::stack< std::pair<int, int> > stackPathToTake = aStar.findPath( 8, GameSettings::mapHeight / 2, selectedXTile, selectedYTile );
    // now that we know we can place the lumber, let's do it
    pGameMap->changeObjectMapTileType(inputXLocation, inputYLocation, TileType::Stump);
    pGameMap->changeObjectMapTileType(whereToPlaceLumber.first, whereToPlaceLumber.second, TileType::UnclaimedLumber);
}
