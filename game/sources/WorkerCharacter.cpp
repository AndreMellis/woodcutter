#include "WorkerCharacter.h"

WorkerCharacter::WorkerCharacter(std::stack< std::pair<int, int> > stkInputPath, WorkerCommand inputCommand )
{
    iLastXTile = -1;
    iLastYTile = -1;
    bTaskHasBeenCompleted = 0;

    stkPathToTake = stkInputPath;
    command = inputCommand;

    pGameMap = Map::getInstance();

    switch(inputCommand)
    { // put any cases where you want a return path here
        case WorkerCommand::GATHER_WOOD_COMMAND:
            while( !stkInputPath.empty() )
            {
                stkReturnPath.push( stkInputPath.top() );
                stkInputPath.pop();
            }
            break;
    }
}

WorkerCharacter::~WorkerCharacter()
{
    while( !stkPathToTake.empty() )
        stkPathToTake.pop();

    while( !stkReturnPath.empty() )
        stkPathToTake.pop();

    pGameMap = nullptr;
}

void WorkerCharacter::step()
{
    if(stkPathToTake.size() > 1)
    { // we still have somewhere to go

        if(iLastXTile < 0 || iLastYTile <0)
        { // this is our first time moving
            iLastXTile = stkPathToTake.top().first;
            iLastYTile = stkPathToTake.top().second;

            pGameMap->changeObjectMapTileType( stkPathToTake.top().first, stkPathToTake.top().second, TileType::Worker );
            stkPathToTake.pop();
        } else
        { // let's just move forward
            pGameMap->changeObjectMapTileType( iLastXTile, iLastYTile, TileType::Empty );
            iLastXTile = stkPathToTake.top().first;
            iLastYTile = stkPathToTake.top().second;

            pGameMap->changeObjectMapTileType( stkPathToTake.top().first, stkPathToTake.top().second, TileType::Worker );
            stkPathToTake.pop();
        }

    } else if ( !bTaskHasBeenCompleted )
    { // the next tile is our dest tile
      // we also haven't done the job yet

        pGameMap->changeObjectMapTileType( iLastXTile, iLastYTile, TileType::Empty );

        // reset the last tiles incase we have a task to head back
        iLastXTile = -1; 
        iLastYTile = -1;

        switch(command)
        {
            case WorkerCommand::HARVEST_COMMAND:
                actions.harvestTree( stkPathToTake.top().first, stkPathToTake.top().second );
                bTaskHasBeenCompleted = 1;
                break;
        }
    } else if( !stkReturnPath.empty() )
    { // now we need to head back
        if( stkReturnPath.size() > 1 )
        {
            if(iLastXTile < 0 || iLastYTile < 0)
            {
                stkReturnPath.pop(); // pop the very first stack item so that we don't delete the stump
                iLastXTile = stkReturnPath.top().first;
                iLastYTile = stkReturnPath.top().second;

                pGameMap->changeObjectMapTileType(stkReturnPath.top().first, stkReturnPath.top().second, TileType::Worker);
                stkReturnPath.pop();
            } else
            { // we can move forward like normal
                pGameMap->changeObjectMapTileType( iLastXTile, iLastYTile, TileType::Empty );
                iLastXTile = stkReturnPath.top().first;
                iLastYTile = stkReturnPath.top().second;

                pGameMap->changeObjectMapTileType( stkReturnPath.top().first, stkReturnPath.top().second, TileType::Worker );
                stkReturnPath.pop();
            }
        } else
        {
            pGameMap->changeObjectMapTileType( iLastXTile, iLastYTile, TileType::Empty );
            stkReturnPath.pop();
        }
    }
}