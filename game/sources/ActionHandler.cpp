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
                    dispatchWorker(WorkerCommand::HARVEST_COMMAND);
                    break;
            }
        }
}

void ActionHandler::dispatchWorker(WorkerCommand command)
{
    if(pGameInventory->idleEmployees <= 0)
        return; // we don't have employees to do the task

    int selectedXTile = pGameMap->getSelectedXIndex();
    int selectedYTile = pGameMap->getSelectedYIndex();
    TileType selectedTileType = pGameMap->getObjectMapTileType( selectedXTile, selectedYTile );

    if( command == WorkerCommand::HARVEST_COMMAND && selectedTileType == TileType::Tree )
    {
        std::stack< std::pair<int,int> > stkPathToTake = aStar.findPath( GameSettings::millXLocation, GameSettings::millYLocation, selectedXTile, selectedYTile );
        if( stkPathToTake.top().first < 0 || stkPathToTake.top().second < 0 )
        { // no path to target
            return; 
        } else
        { // this tree is good to harvest
            pGameInventory->idleEmployees--;
            lisWorkers.push_back( new WorkerCharacter( stkPathToTake, WorkerCommand::HARVEST_COMMAND ) );
        }
    }
}

void ActionHandler::step()
{
    aStar.updateNodeMap();

    for( auto worker=lisWorkers.begin(); worker != lisWorkers.end(); )
    {
        if( (*worker)->workerCanBeDeleted() )
        { // worker has completed it's task
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