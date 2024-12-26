#include "WorkerCharacter.h"

WorkerCharacter::WorkerCharacter(std::stack< std::pair<int, int> > stkInputPath, WorkerCommand inputCommand )
{
    iLastXTile = -1;
    iLastYTile = -1;
    bTaskHasBeenCompleted = 0;

    stkPathToTake = stkInputPath;
    command = inputCommand;

    pGameMap = Map::getInstance();
}

WorkerCharacter::~WorkerCharacter()
{
    while( !stkPathToTake.empty() )
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

    } else
    { // the next tile is our dest tile

        pGameMap->changeObjectMapTileType( iLastXTile, iLastYTile, TileType::Empty );

        switch(command)
        {
            case WorkerCommand::HARVEST_COMMAND:
                actions.harvestTree( stkPathToTake.top().first, stkPathToTake.top().second );
                bTaskHasBeenCompleted = 1;
                break;
        }
    }
}