#ifndef DAYTIME_HEADER_
#define DAYTIME_HEADER_

#include <SDL3/SDL.h>
#include "Inventory.h"

class DayTime
{
private:
    Inventory *pGameInventory;
    Uint64 mStartTicks; // computer start time when the game started
    Uint64 mCountedTicks;

    const int millisecondsInGameDay = 1000 * 60 * 5; // 1000 milliseconds * 60 secs in min * 5 min = 5 minutes per day

public:
    DayTime();
    void init( Inventory *inputInventory );
    void progress();
};

#endif