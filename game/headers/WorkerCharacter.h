#ifndef WORKERCHARACTER_HEADER_
#define WORKERCHARACTER_HEADER_

#include <stack>
#include <utility>
#include "Map.h"
#include "Tile.h"
#include "Actions.h"

enum class WorkerCommand
{
    HARVEST_COMMAND,
    GATHER_WOOD_COMMAND
};

class WorkerCharacter
{
private:
    std::stack< std::pair <int, int> > stkPathToTake;
    std::stack< std::pair <int, int> > stkReturnPath;

    int iLastXTile;
    int iLastYTile;
    bool bTaskHasBeenCompleted;
    
    WorkerCommand command;
    Actions actions;
    Map *pGameMap;

public:
    WorkerCharacter(std::stack< std::pair<int, int> > stkInputPath, WorkerCommand inputCommand );
    ~WorkerCharacter();

    void step();
    bool workerCanBeDeleted() { return bTaskHasBeenCompleted && stkReturnPath.empty(); }

    WorkerCommand getCommand() { return command; } // mainly because I want handler to handle inventory
};

#endif