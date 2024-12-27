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
                    dispatchWorker();
                    break;
            }
        }
}

void ActionHandler::dispatchWorker()
{
    if(pGameInventory->idleEmployees <= 0)
        return; // we don't have employees to do the task

    int selectedXTile = pGameMap->getSelectedXIndex();
    int selectedYTile = pGameMap->getSelectedYIndex();

    if(selectedXTile < 0 || selectedYTile < 0)
        return; // no tile selected

    std::stack< std::pair<int,int> > stkPathToTake = aStar.findPath( GameSettings::millXLocation, GameSettings::millYLocation, selectedXTile, selectedYTile );
    if( stkPathToTake.top().first < 0 || stkPathToTake.top().second < 0 )
        return; // no path to target

    TileType selectedTileType = pGameMap->getObjectMapTileType( selectedXTile, selectedYTile );
    switch( selectedTileType )
    {
        case TileType::Tree:
            pGameInventory->idleEmployees--;
            lisWorkers.push_back( new WorkerCharacter( stkPathToTake, WorkerCommand::HARVEST_COMMAND ) );
            break;
        case TileType::UnclaimedLumber:
            pGameInventory->idleEmployees--;
            lisWorkers.push_back( new WorkerCharacter( stkPathToTake, WorkerCommand::GATHER_WOOD_COMMAND ) );
            break;

    }

    if( selectedTileType == TileType::Tree )
    {
    }
}

void ActionHandler::step()
{
    aStar.updateNodeMap();

    for( auto worker=lisWorkers.begin(); worker != lisWorkers.end(); )
    {
        if( (*worker)->workerCanBeDeleted() )
        { // worker has completed it's task
            switch ( (*worker)->getCommand() )
            { // update inv before cleanup
                case WorkerCommand::GATHER_WOOD_COMMAND:
                    pGameInventory->wood++;
                    break;
            }

            delete *worker; // call WorkerCharacter's deconstructor
            worker = lisWorkers.erase(worker); // remove the pointer from the list and point to next item
            pGameInventory->idleEmployees++;
        } else
        { // the worker still has work to do
            (*worker)->step();
            ++worker; // this is wierd but you have to manually move to next item
        }
    }
}