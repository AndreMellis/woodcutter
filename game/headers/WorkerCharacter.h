#ifndef WORKERCHARACTER_HEADER_
#define WORKERCHARACTER_HEADER_

#include <stack>
#include <utility>
#include "Map.h"
#include "Tile.h"
#include "Actions.h"

enum class WorkerCommand
{
    HARVEST_COMMAND
};

class WorkerCharacter
{
private:
    std::stack< std::pair <int, int> > stkPathToTake;

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
    bool workerCanBeDeleted() { return bTaskHasBeenCompleted; }
};

#endif