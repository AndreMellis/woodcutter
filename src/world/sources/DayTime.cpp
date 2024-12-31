#include "DayTime.h"

DayTime::DayTime()
{
    pGameInventory = nullptr;
}

void DayTime::init( Inventory *inputInventory )
{
    pGameInventory = inputInventory;
    mStartTicks = SDL_GetTicks();
}

void DayTime::progress()
{
    mCountedTicks += ( SDL_GetTicks() - mStartTicks );

    if(mCountedTicks >= millisecondsInGameDay)
    { // time to progress a day
        pGameInventory->day++;

        if( pGameInventory->day > 7)
            pGameInventory->day = 1;

        mStartTicks = SDL_GetTicks(); // restart the main timer
        mCountedTicks = 0;
    }
}