#ifndef ACTIONHANDLER_HEADER_
#define ACTIONHANDLER_HEADER_

#include <SDL3/SDL.h>
#include <utility>
#include <stack>
#include <list>

#include "WorkerCharacter.h"
#include "GameSettings.h"
#include "Inventory.h"
#include "AStar.h"
#include "Map.h"

class ActionHandler
{
private:
    Inventory *pGameInventory;
    Map *pGameMap;

    AStar aStar;

    std::list<WorkerCharacter*> lisWorkers;

public:
    ActionHandler();

    void init(Inventory *pGameInv);

    void dispatchWorker(WorkerCommand command);

    void handleEvent(SDL_Event &event);
    void step(); // this will handle things we do once a frame
};

#endif